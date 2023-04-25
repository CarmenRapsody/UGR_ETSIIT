/*
ejercicio2.c
El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los
permisos de todos los archivos que se encuentren en el directorio indicado en el primer
argumento.

Compilación
		gcc -std=c11 -Wall -o ejercicio2 ejercicio2.c

*/

#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>


int main(int argc, char *argv[]){
  DIR *direct;
  unsigned int permisos;
  char *pathname;

  struct stat atributos;
  struct dirent *entrada;
  char cadena[100];
  char cadena2[100];


  /* Check args*/
  if (argc==3){
    pathname=argv[1];
    direct=opendir(pathname);
    permisos=strtol(argv[2],NULL,8); //pasamos la cadena(str) a entero (long int)
  }
  else{
    printf("\n Uso: Introduzca %s <directorio>  <permisos> \n\n", argv[0]);
	  exit(EXIT_FAILURE);
  }

  
  while((entrada=readdir(direct)) != NULL){ //mientras no lleguemos al fin del directorio
    sprintf(cadena,"%s/%s",pathname,entrada->d_name);

    if(stat(cadena,&atributos) < 0){
      printf("\nError al intentar acceder a los atributos de archivo");
      perror("\nError en lstat");
      exit(EXIT_FAILURE);
    }

    if(S_ISREG(atributos.st_mode)){ //si archivo regular
      sprintf(cadena2,"%s",entrada->d_name);  //nombre
      printf("%s: %o ",cadena2 ,atributos.st_mode); //tipo de archivo y permisos
      chmod(cadena,permisos); //cambiamos los permisos

      if(chmod(cadena,permisos) < 0) {
        exit(EXIT_FAILURE);
      }
   }

   closedir(direct);
   return 0;
}