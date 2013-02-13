/*
  Libreria de conexion a Base de Datos
  "METODO DE APLICACION DEL PROTOCOLO DE REPARTO DE SECRETOS ESQUEMA ADI SHAMIR"
  Creado por Diego Mendoza (Damphell).
 */
#ifndef _CONNECT_DB_H
#define _CONNECT_DB_H

//Cabeceras de las librerias para acceder a los diferentes gestores de BD.
#include <mysql/mysql.h>
#include <postgresql/libpq-fe.h>

#include "lib_com.h"

//Variables para mysql
MYSQL *conn;
MYSQL_RES *res; 
MYSQL_ROW row;
//Variables para postgresql


//variables de consulta
char server[60];
char user[60];
char password[60];
char database[60];
char nombre_tabla[60];
char campo_usuario[60];
char campo_pass[60];

//Variable para consulta SQL
  char sql[200];

int actualiza_datos(char datosBD[][60], int selDB, unsigned long int sec);
int autentica_secreto(char datosBD[][60], int selDB, unsigned long int sec);

#endif
