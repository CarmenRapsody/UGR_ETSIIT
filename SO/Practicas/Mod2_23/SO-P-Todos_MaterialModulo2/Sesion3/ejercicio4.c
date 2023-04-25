/*
ejercicio4.c
Compilación
		gcc -std=c11 -Wall -o ejercicio4 ejercicio4.c

*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  const int NUM_HIJOS = 5;
  pid_t pid[NUM_HIJOS];

  //creacion de hijos
  for(int i=0; i<NUM_HIJOS; i++){
    if((pid[i]=fork())==0){
      printf("Soy el hijo de %d\n",getpid() );
      break;
    }
    else if(pid[i]<0){
      printf("Error al crear el hijo");
      exit(EXIT_FAILURE);
    }
  }

//lanzo a los hijos
  for(int i=0;i<NUM_HIJOS; i++){
    if(waitpid(pid[i],0,0)>0){
      printf("Acaba de finalizar mi hijo con PID: %d\n",pid[i]);
      printf("Solo me quedan %d hijos vivos \n", NUM_HIJOS-(i+1));
    }
  }

  return 0;



}