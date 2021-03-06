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

#include "reparto.h"
//Inicio Fecha 20-Marzo-2012 by Diego Mendoza (damphell)
//procedimientos para Fase I del Protocolo de Reparto de Secretos

//Funcion que genera el polinomio de grado k-1
void genera_poli(int k, unsigned long int s, unsigned long int poli[], int dim)
{
  int i;
  int aux=1;
  srand((unsigned int)time(0));
  for(i=0;i<dim-2;i=i+2)
  {
    poli[i] = (rand()%(100-0+1));
    poli[i+1] = (k-aux);
    aux++;
  }
  poli[dim-2] = s;
  poli[dim-1] = k-aux;
}
//Funcion para mostrar polinomio
void mostrar_poli(unsigned long int v[], int t)
{ int i;
  printw("\n\n Polinomio Origen (Generado Aleatoriamente): \n\n");
  printw(" ==> ");
  for(i=0;i<t-2;i=i+2)
  {
    printw("%ldx^%ld + ",v[i],v[i+1]);
  }
  printw("%ld",v[i]);
  //printw("\n");
}

//funcion de elebar exponencia
unsigned long int powp(long int x, long int y)
{
  int i;
  int resp=1;
  if((y>=0)&&(x>0))
  {
    for(i=1;i<=y;i++)
    {
      resp=resp*x;
    }
    return resp;
  }  
  return 0;
}
/////
unsigned long int valor_x(long int x,unsigned long int poli[],int dim)
{
  int i;
  unsigned long int y=0; //Es el valor resultado de la operacion del polinomio
  for(i=0;i<dim;i=i+2)
  {
    y = y + (poli[i]* (powp(x,poli[i+1])));
  }  
  return y;
}
//Generacion de Sombras
void genera_sombras(int n, unsigned long int poli[], int dim, unsigned long int sombras[][2])
{
  //unsigned long int sombras[n][2];
  int j; //Variable Auxiliar para la operacion del arreglo
  int i;
  short int max = 99, min = 40;
  srand((unsigned int)time(0)); //Funcion para generar numeros aleatorios
  int band=0;
  for(j=0;j<n;j++)
  {
    //srand((unsigned int)time(0));
    sombras[j][0]= (rand()%(max-min+1))+min;
    band=0;
    if(j>0)
    { 
      while(band!=1)
      {
	if(labs(sombras[j-1][0]-sombras[j][0])<6)
	{
	  band=1;
	}
	else
	{
	  sombras[j][0] = (rand()%(max-min+1))+min;
	}  
        
        for(i=0;i<j;i++)
	{
	  if(sombras[i][0]==sombras[j][0])
	  {
	    sombras[j][0] = (rand()%(max-min+1))+min;
 	    band=0;
	  }  
	}
      }  	
    }  
    sombras[j][1] = valor_x(sombras[j][0],poli,dim);
    //printf("Sombra %d (%ld,%ld) \n",j,sombras[j][0],sombras[j][1]);
  }
}
//Funcion Principal para la Fase 1 del protocolo de reparto de Secretos
//Variable K = Representa el valor umbral
//Variable n = Representa el número de sombras a generar
//Variable s = Representa el secreto a resguardar y a repartir
//Variable sombras[][2] = Representa al contenedor de las sombras a devolver
void fase_1(int k, int n, unsigned long int s, unsigned long int sombras[][2])
{
  int dim;
  dim = k*2;
  unsigned long int polin[dim];
  genera_poli(k,s,polin,dim);
  genera_sombras(n,polin,dim,sombras);
  //Habilitar la funcion mostrar_poli() si quiere observar el polinomio origen
  //que da lugar a las parejas de valores.
  mostrar_poli(polin,(k*2));
}
