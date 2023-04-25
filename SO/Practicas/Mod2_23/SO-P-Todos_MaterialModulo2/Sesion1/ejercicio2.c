/*
ejercicio2.c
Procesar un archivo de entrada en bloques de 80 caracteres y escribir en un archivo 
de salida, salida,txt, los chunks encabezados con "Bloque1"

Compilación
		gcc -std=c11 -Wall -o ejercicio2 ejercicio2.c

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[])
{
int fde, fds; //fde: file descriptor entrada //fds: file descriptor salida
char buffer[80];


/* Check args*/
if(argc<2){
	printf("\n Uso: Introduzca %s <fichero>\n\n", argv[0]);
	exit(EXIT_FAILURE);
}

//Crea el archivo de salida
if( (fds=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	perror("\nError en el primer open");
	exit(EXIT_FAILURE);//estandar de error
}

//abre le archivo pasado como argumento
//doble parentesis para asignar el valor de una funcion
if( (fde=open(argv[1],O_RDONLY)) <0 ) {
	perror("\nError en el segundo open");
	exit(EXIT_FAILURE);//estandar de error
}

int i=1;
char str[50];
int leidos = 0;

while((leidos=read(fde,buffer,80*sizeof(char)))!=0){
  /*Encabezado*/
  sprintf(str,"\n\nBloque %i\n\n", i);

  //Escribe en el archivo de salida el encabezado
  if(write(fds,str,(strlen(str)*sizeof(char))) !=(strlen(str)*sizeof(char)) ){
  	perror("\nError en primer write");
  	exit(EXIT_FAILURE);
  }

  //Escribe en el archivo de salida el chunk
  if(write(fds,buffer,leidos*sizeof(char)) != leidos*sizeof(char)) {
  	perror("\nError segundo write");
  	exit(EXIT_FAILURE);
  }

  i++;
}
close(fde);
close(fds);
return EXIT_SUCCESS;
}