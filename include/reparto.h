/*
  Crado por Diego Mendoza (Damphell) para TESIS "METODO DE APLICACION
  DEL PROTOCOLO DE REPARTO DE SECRETOS"
  Libreria reparto.h para hacer referencia a la libreria
  reparto.c y poder usar sus funciones
 */
#ifndef _REPARTO_H
#define _REPARTO_H

#include "lib_com.h"

#define MAXCOL 100
//Aqui se define las funciones de reparto.c.
void genera_poli(int k, unsigned long int s, unsigned long int poli[], int dim);
void mostrar_poli(unsigned long int v[], int t);
unsigned long int powp(long int x, long int y);
unsigned long int valor_x(long int x,unsigned long int poli[],int dim);
//void genera_sombras(int n, unsigned long int poli[], int dim);
void genera_sombras(int n, unsigned long int poli[], int dim, unsigned long int sombras[][2]);
//void fase_1(int k, int n, unsigned long int s);
void fase_1(int k, int n, unsigned long int s, unsigned long int sombras[][2]);
#endif 
