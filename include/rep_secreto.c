/*
 Copyright 2012 Diego Mendoza (damphell)

 This file is part of "METODO DE APLICACION DEL PROTOCOLO DE REPARTO DE 
 SECRETOS - ESQUEMA ADI SHAMIR", it's a library for C/C++.

 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rep_secreto.h"

//Usa las libreras para repartir el secreto
//Funcion que usa la libreria reparto.c generando el secreto aleatoriamente.
int genera_reparto_aleatorio(int k, int n, unsigned long int sombras[][2], char datosBD[][60], int selBD)
{
  /* ERRORES
     0 ==> Si, no hay conexion a BD
     1 ==> Si, la operacion fue exitosa
  */
  unsigned long int secreto;
  unsigned long int max = 999999999999;
  unsigned long int min = 10000000;
  
  int auxbd = 0; //Variable controla errores
   
  srand((unsigned long int)time(0));
  secreto = (rand()%(max-min+1))+min;

  ////Para demostracion
  printw("\n\n Generando Secreto Aleatorio......\n");
  printw("\n ==> Secreto generado: %ld \n",secreto);
   ///////

  //Conexion a al GDB para almacenar el secreto
  switch(selBD)
  {
  case 1: auxbd = actualiza_datos(datosBD,1,secreto);
    //printw("\n\n resultado de conexxion %d ....\n",auxbd); 
          break;
  case 2: auxbd = actualiza_datos(datosBD,2,secreto);
          break;
  default: exit(1);
          break;
  } 
  //
  fase_1(k,n,secreto,sombras);
  return auxbd;
}

//Funcion que reparte las sombras por correo
void sombras_correo(int n, unsigned long int sombras[][2],char dir_correos[][50],char datos_local[][50])
{
  //Datos que vienen desde datos_local
  char correo_orig[50]; //datos_local[0]
  char usuario[50]; //datos_local[1]
  char pass[30]; //datos_local[2]
  char serv[30]; //datos_local[3]
  int port;
  
  strcpy(correo_orig,datos_local[0]);
  strcpy(usuario,datos_local[1]);
  strcpy(pass,datos_local[2]);
  strcpy(serv,datos_local[3]);
  port = atoi(datos_local[4]);
  //char correo_dest[50];
  int i;

  char file[11];
  char aux_n[1];
  unsigned long int pareja[2];
  char cmd_send[500];

  strcpy(file,"secr_");

  if(n > 1)
  {
    for(i=0;i<n;i++)
    {
      sprintf(aux_n,"%d",i);
      strcat(file,aux_n);
      strcat(file,".rps");
    
      pareja[0] = sombras[i][0];
      pareja[1] = sombras[i][1];
      
      
      genera_archivo(file,pareja);
      //cifra_archivo(file);
      //Ahora se Envia por correo
      sprintf(cmd_send,"./include/mailsend/mailsend -to %s -from %s -smtp %s -port %d -sub \"Sistema Secreto\" -M \"Mensaje Generado por el Sistema....\" -attach \"%s\" -auth-login -user %s -pass \'%s\'",dir_correos[i],correo_orig,serv,port,file,usuario,pass);
       system(cmd_send);
      //luego de enviarlo eliminamos el archivo.
      elimina_archivo(file);      
      //
      strcpy(file,"secr_");
    }
  }  
}

//Funcion que crea un archivo, con una pareja de valores
void genera_archivo(char file[11],unsigned long int par_val[])
{
  FILE *archivo;
  
  archivo = fopen(file,"w");
  //Aqui colocamos la pareja de valores en la estructura de 
  //archivos.
  rep_file.parte_x = par_val[0];
  rep_file.parte_y = par_val[1];
  //
  fwrite(&rep_file,sizeof(struct rep_archivo),1,archivo);
  fclose(archivo);
  ///
  printw("\n Archivo de Pareja %s creado y enviado",file);
  ////
  //cifra_archivo(archivo,file);
  return;
}
//void cifra_archivo(FILE *archivo, char file[11])
void cifra_archivo(char file[11])
{
  char cmd[150];
  FILE *archivo;

  archivo = fopen(file,"r");
  if(archivo)
  {
    fclose(archivo);
    sprintf(cmd,"echo \"academy2012\" | gpg -seav --yes -r shamir -o %s  --passphrase-fd O %s",file,file);
    system(cmd);
  }  
  //  printf("\n %s \n",cmd);
}
//Funcion que elimina archivo despues de haberla creado y el secreto fue repartido
void elimina_archivo(char file[60])
{
  char cmd[70];
  sprintf(cmd,"rm %s",file);
  system(cmd);
}

///Funciones para la fase 2, recuperar secreto a partir de los archivos generados.
///Recupera el secreto a partir de los archivos.
int recupera_acceso(char directorio[100], char datosBD[][60], int selBD)
{
  unsigned long int sombras[MAX][2]; //Matriz para recuperar las sombras desde los archivos
  int ks = 0; //Numero de sombras recuperadas
  unsigned long int sombra[2]; //Vector de 2 elementos auxiliar para recuperar una unica pareja.
  int retorno = 0; //Valor de retorno al sistema principal que lo invoca
  ///Aqui se arma la matriz con los secretos recuperados desde los archivos
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
  struct dirent *ent;

  /* Empezaremos a leer en el directorio actual que enviamos en la variable directorio*/
  dir = opendir (directorio);

  /* Miramos que no haya error */
  if (dir == NULL)
    error("No puedo abrir el directorio");
 
     /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
     /* Leyendo uno a uno todos los archivos que hay */
    while ((ent = readdir (dir)) != NULL)
    {
      /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
      {
	/* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
	procesoArchivo(ent->d_name,directorio,sombra);
	sombras[ks][0] = sombra[0];
	sombras[ks][1] = sombra[1];
	ks++;
      }
    }
  closedir (dir);
  retorno = recupera_secreto(ks,sombras,datosBD,selBD);
  return retorno;
  //  return EXIT_SUCCESS;
}
void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}
void procesoArchivo(char *archivo, char dir[], unsigned long int sombra[])
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: http://totaki.com/poesiabinaria/2010/04/tamano-de-un-fichero-en-c/ */
  FILE *fich;
  long ftam;
  char dir_arch[60];
  strcpy(dir_arch,dir);
  strcat(dir_arch,archivo);
  fich = fopen(dir_arch, "r");
  printw("\n el archivo %s ",dir_arch);
     if(fich == NULL)
     {
       printw("\nFichero no existe! \nPor favor creelo");
       
       //       return;
     }
  if (fich)
  {
      ////Una vez obtenido el nombre del archivo recuperamos la pareja obtenida.
      //fread(&registro, sizeof(struct sRegistro), 1, Fichero);
      fread(&rep_file,sizeof(struct rep_archivo),1,fich);
      while(!feof(fich))
      {
        printw("\n entrando .......");
                //fread(&registro, sizeof(struct sRegistro), 1, Fichero);
		//                numero++;
	fread(&rep_file,sizeof(struct rep_archivo),1,fich);
	sombra[0] = rep_file.parte_x;
	sombra[1] = rep_file.parte_y;
	printw("\n \tx= %ld y= %ld",sombra[0],sombra[1]);
      }
     //if(!feof(fich))
      //{
	//}
      //////
      	fseek(fich, 0L, SEEK_END);
	ftam=ftell(fich);

	fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      printw ("%30s (%ld bytes)\n", archivo, ftam);
      elimina_archivo(dir_arch);
    }
    else
    {  
    /* Si ha pasado algo, sólo decimos el nombre */
      printw ("%30s (No info.)\n", archivo);
    }
}

///
int recupera_secreto(int ks, unsigned long int sombras[][2], char datosBD[][60], int selBD)
{
  unsigned long int secreto;
  secreto = fase_2(ks,sombras);
  int retorno = 0;
  printw("\n El secreto recuperado es: %ld \n",secreto);
  if(autentica_secreto(datosBD,selBD,secreto) == 1)
  {
    ///autenticacion y recuperacion exitosa
    retorno = 1;
  }
  else
  {
    ///autenticacion fallida!!!!
    retorno = 0;
  }
  return retorno;
}
