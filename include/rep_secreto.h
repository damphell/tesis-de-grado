/*
  Libreria Principal del 
  "METODO DE APLICACION DEL PROTOCOLO DE REPARTO DE SECRETOS ESQUEMA ADI SHAMIR"
  Creado por Diego Mendoza (Damphell).
 */
#ifndef _REP_SECRETO_H
#define _REP_SECRETO_H

//Cabeceras de las librerias
#include "lib_com.h"
#include "connectDB.h"
#include "reparto.h"
#include "recup.h"
#include "estruct.h"

#define MAX 100

//Aqui se define las funciones de rep_secreto.h

//Usa las libreras para repartir el secreto
/*+Funcion que usa la libreria reparto.c generando el secreto aleatoriamente.+*/
int genera_reparto_aleatorio(int k, int n, unsigned long int sombras[][2], char datosBD[][60], int selBD);
void sombras_correo(int n, unsigned long int sombras[][2],char dir_correos[][50],char datos_local[][50]);
void genera_archivo(char file[11],unsigned long int par_val[]);
//void cifra_archivo(FILE *archivo, char file[11]);
void cifra_archivo(char file[11]);
void elimina_archivo(char file[11]);

////Fase 2 recupera secreto
void error(const char *s);
void procesoArchivo(char *archivo, char dir[], unsigned long int sombra[]);
int recupera_acceso(char directorio[100], char datosBD[][60], int selBD);
int recupera_secreto(int ks, unsigned long int sombras[][2], char datosBD[][60], int selBD);


#endif
