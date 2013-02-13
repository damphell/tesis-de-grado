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

#include "recup.h"

//Funciones Fase_2, RECUPERACION DEL SECRETO
/////////////////////////////////////////////

void monomio(int n, double x[], double D[])
{
 
  double E[n];
  D[0] = 1;
  D[1] = x[0];
  int i,j,k;
  for (i = 1; i < n; i++) {
      for (k =1; k < i+1; k++) {
         E[k] = D[k] + D[k-1]*x[i];
      }
      D[i+1] = D[i]*x[i];
      for (j = 1; j < i+1; j++) {
         D[j] = E[j];
      }
   }
}
long int pDenominador(int x, double xn[], int tam)
{ int i;
  double sum = 1;
  for(i=0;i<tam;i++)
  {
     sum = sum * (x+xn[i]);
  }
  ///
  char rp[20];
  ///
  sprintf(rp,"%0.0f",sum);
  return atoi(rp);
}
void genera_matrizpol(unsigned long int sombras[][2], double (*pol)[MAXCOL],int k, int c )
{
  int vec=k, vec2=k-1;
  double D[k], x[vec];
  double x1[vec2];
  int aux = 0;
  int i,j,yy=0;

  for(i=0;i<vec;i++)
  {
    x[i]= sombras[i][0];
    x[i] = x[i] * -1;
  }
  for(i=0;i<k;i++)//Controla las filas de la matriz de polinomios
  {
    aux=(-1)*x[i];
    for(j=0;j<vec;j++)
    { 
      if(j!=i)
      {
	x1[yy]=x[j];
        yy++;
      }
    }
    yy=0; 
    monomio(k,x1,D);
    for(j=0;j<c-1;j++) 
    {
       pol[i][j]=D[j];
    }
    pol[i][c-1]= pDenominador(aux,x1,vec2);
  }
}
unsigned long int genera_polinomio(unsigned long int sombra[][2], double poli[][MAXCOL], int f, int col)
{
  int nf;
  nf = f * 2;
  double res[nf];
  double sum = 0;
  double yy[f];
  int j,i;
  int aux = 0, exp = f-1;

  for(i=0;i<f;i++)
  {
    yy[i]= sombra[i][1];
  }  
  for(j=0;j<col-1;j++)
  {
    sum = 0;
    for(i=0;i<f;i++)
    {
      sum = sum + (yy[i]*(poli[i][j]/poli[i][col-1]));
    }
    res[aux] = sum;
    res[aux+1] = exp;
    aux = aux + 2; exp--; 
  }

  //En esta parte mostramos el resultado de todo el procedimiento
  //de recuperación del secreto.
  
  //Demossss
  printw("\n Recuperando polinomio origen:  \n\n ");
  for(i=0;i<nf-2;i=i+2)
  {
           printw("%0.0fx^%0.0f + ",res[i],res[i+1]);
  }
  
  //printw("\n\n");
  printw("%0.0f",res[i]);
  char resultado[14];
  sprintf(resultado,"%0.0f",res[i]);
  //printw("\n El sec es: %ld",xxx);
  printw("\n");
  ////
  return atoi(resultado);
}
unsigned long int recu_secre(int ks, unsigned long int sombras[][2])
{ 
  int f=ks, col=ks+1;
  // col=ks+1;
  double poli[f][100];

  genera_matrizpol(sombras,poli,f,col);

  /* int i,j;
  
  for(i=0;i<f;i++)
  {
    for(j=0;j<col;j++)
    {
      printf("%0.0f \t",poli[i][j]);
    }
    printf("\n");  
    } */ 
  return genera_polinomio(sombras,poli,f,col);
  
}
/*
  ks ==> Corresponde a la cantidad de sombras requeridas
  sombras ==> Corresponde a la pareja de sombras a leer.
*/
unsigned long int fase_2(int ks, unsigned long int sombras[][2])
{ 
  return  recu_secre(ks,sombras);
}
