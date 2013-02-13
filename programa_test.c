#include <stdio.h>

#include "include/rep_secreto.h"
#include <ncurses.h>
//funcion principal
int main()
{ 
  int n = 4; //numero de sombras a generar
  int k = 3; //numero de minimo de sombras requeridas. 
  unsigned long int sombras[n][2];
  char datbd[7][60]={"127.0.0.1","damphell","academy","protocolo_reparto","user","nombre_usuario","password"};
  
  /////
  char local[5][50] = {"ketano@ketanolab.com","ketano@ketanolab.com","ketano","correo.ketanolab.com","25"};
  char correos[20][50] = {"dmendoza@soltux.com","diegomcsb@gmail.com","abel_amp@hotmail.com"};
  ////
  int seldb = 1;

  ////Variables para demostracion de comportamiento de libreria
  int opcion = 4;
  char directorio[100];
  int  auth = 0;
  ///control de errores
  int genera = 0;
  int sombras_c = 0;
  int recupera_s = 0;

  initscr();
    
  do{
    printw("\n=========== METODO DE APLICACION DEL PROTOCOLO DE REPARTO DE SECRETOS===========\n");
    printw("====================COMPORTAMIENTO DEL MODULO COMPUTACIONAL=====================\n");
    printw("\n[1] Generar Secreto Aleatorio y almacenar en Base de Datos.");
    printw("\n[2] Compartir el secreto.");
    printw("\n[3] Recuperar el Secreto y Autenticarse.");
    printw("\n[4] Salir Desmotración.\n");
    printw("\n    Escoger Opcion: ");
    scanw("%d",&opcion);
    switch(opcion){
    case 1:erase();
           printw("\n Generar Secreto Aleatoriamente y almacenarlo en Base de Datos\n");
	   printw("\n Insertar Parametros..\n\n ");
	   printw("Insertar número de sombras requeridas (K): ");
	   scanw("%d",&k);
	   printw(" Insertar número de sombras a generar (n): ");
	   scanw("%d",&n);
	   printw("\n Datos de conexion a Base de Datos... \n ");
	  
	   printw("Direccion IP o Nombre del Servidor de base de datos: ");
	   scanw("%s",&datbd[0]);
	   printw(" Nombre de usuario en base de datos: ");
	   scanw("%s",&datbd[1]);
	   printw(" Clave de acceso a base de datos: ");
	   scanw("%s",&datbd[2]);
	   printw(" Nombre base de datos: ");
	   scanw("%s",&datbd[3]);
	   printw(" Tabla perteneciente de Base de Datos: ");
	   scanw("%s",&datbd[4]);
	   printw(" Nombre campo, correspondiente a usuario: ");
	   scanw("%s",&datbd[5]);
	   printw(" Nombre campo, clave de acceso usuario: ");
	   scanw("%s",&datbd[6]);
	   printw(" Seleccionar Gestor de Base de Datos MySQL[1], PostgreSQL[2]: ");
	   scanw("%d",&seldb);
	   //printw("datos %s, %s, %s, %s, %s, %s, %s",datbd[0],datbd[1],datbd[2],datbd[3],datbd[4],datbd[5],datbd[6]);
	   erase();
	   genera = genera_reparto_aleatorio(k,n,sombras,datbd,seldb);
	   if(genera == 1){
	     /////valor por exito
	     printw("\n\n Conectado con Base de Datos: %s \n",datbd[3]);
	     printw("\n ==> Secreto almacenado correctamente!!!");
	   }
	   else
	   {
	     printw("\n Fallo en conexion!!!");
	     endwin();
	     exit(1);
	   }
	   getch();
      break;
    case 2:erase();
      //      char local[5][50] = {"ketano@ketanolab.com","ketano@ketanolab.com","ketano","correo.ketanolab.com","25"};
      //      char correos[3][50] = {"dmendoza@soltux.com","diegomcsb@gmail.com","abel_amp@hotmail.com"};
           printw("\n Enviando Sombras por Correo...\n");
	   printw("\n Insertar Parametros..\n\n ");
	   printw("Insertar Datos de correo local..\n\n");
	   printw(" Inserte direccion de correo electronico: ");
	   scanw("%s",&local[0]);
	   printw(" Inserte nombre de usuario de correo electronico: ");
	   scanw("%s",&local[1]);
	   printw(" Password de Correo electronico: ");
	   scanw("%s",&local[2]);
	   printw(" Inserte direccion del servidor de correo: ");
	   scanw("%s",&local[3]);
	   printw(" Inserte puerto SMTP (25): ");
	   scanw("%s",&local[4]);
	   
	   //
	   printw("\n Insertar direcciones de correo de los %d participantes...\n\n",n);
	   int ii;
	   for(ii=0;ii<n;ii++)
	   {
	     printw(" Correo participante [%d]: ",ii+1);
	     scanw("%s",&correos[ii]);
	   }
           //Enviando por correo las sombras generadas
	   erase();
	   printw("\n Generando Archivos para enviar....\n");
	   sombras_correo(n,sombras,correos,local);
	   //	   initscr();
	   getch();
      break;
    case 3:erase();
           printw("\n Fase 2: Recuperación del Secreto................\n");
	   printw("\n Insertar Directorio de busqueda: ");
	   scanw("%s",&directorio);
           //prueba para recuperacion de claves.
           //printf("\n\nRecuperando.......\n");
	   //recupera_acceso("./tmp/");
	   erase();
	   printw("\n Leyendo archivos.......\n");
	   printw(" ==> Generando Parejas de Valores.....\n");
	   printw("\n Recuperando Secreto......\n");
	   	   
	   auth = recupera_acceso(directorio,datbd,seldb);
	   printw("\n Autenticando.............\n");

	   if( auth == 1){
	     printw("\n Recuperacion del Secreto Exitosa!!!");
	   }
	   else{
	     printw("\n Recuperacion del Secreto Fallida!!!");
	   }
	   getch();
      break;
    case 4:
      break;
    default : //opcion = 4;
             printw("\n Escoja opcion correcta.....\n");
	     getch();

      //      system("clear");
      break;
    }
    erase();
  }while(opcion != 4);
  //printw("\n\n************ FIN ***********\n");
  endwin();
  return 0;
}
