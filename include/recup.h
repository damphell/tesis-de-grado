/*
  Crado por Diego Mendoza (Damphell) para TESIS "METODO DE APLICACION
  DEL PROTOCOLO DE REPARTO DE SECRETOS"
  Libreria recup.h para hacer referencia a la libreria
  recup.c y poder usar sus funciones
 */
#ifndef _RECUP_H
#define _RECUP_H

#include "lib_com.h"

#define MAXCOL 100
//Aqui se define las funciones de recup.c.

void monomio(int n, double x[], double D[]);
long int pDenominador(int x, double xn[], int tam);
void genera_matrizpol(unsigned long int sombras[][2], double (*pol)[MAXCOL],int k, int c );
unsigned long int genera_polinomio(unsigned long int sombra[][2], double poli[][MAXCOL], int f, int col);
unsigned long int recu_secre(int ks, unsigned long int sombras[][2]);
unsigned long int fase_2(int ks, unsigned long int sombras[][2]);

#endif 
