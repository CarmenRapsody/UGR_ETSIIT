/*
ejercicio5.c
Implementa una modificación sobre el anterior programa (ejercicio4)
en la que el proceso padre espera primero a los hijos creados en orden
impar (1º,3º,5º) y después a los hijos pares (2º y 4º).

Compilación: 
    gcc -std=c11 -o ejercicio5 ejercicio5.c


*/

#include <sys/types.h>	
#include <unistd.h>		
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>	
#include <sys/wait.h>	

const int NUM_HIJOS = 5;

int main(int argc, char *argv[]){
	int num_hijos = 0;
	int PIDs[NUM_HIJOS];
	int estado;

	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}

	for (int i=1 ; i<=NUM_HIJOS ; i++) {
		if ( (PIDs[i-1]=fork()) < 0 ) {
			printf("Error %d al crear el hijo %d\n",errno,i);
			perror("Error en la creación del hijo\n");
			exit(EXIT_FAILURE);
		}else
			num_hijos++;

		// si es un hijo termino
		if(PIDs[i-1] == 0){
			printf("Soy el hijo %d: %d\n", i, getpid());
			exit(estado);
		}
	}

	sleep(2);

//hijos creados impares
	for(int i=0 ; i<NUM_HIJOS; i+=2){
		waitpid(PIDs[i],&estado,0);
		num_hijos--;
		printf("\nAcaba de finalizar el proceso %d\n", PIDs[i]);

		if(num_hijos>0)
			printf("Sólo me quedan %d hijos vivos\n", num_hijos);
		else
			printf("No me quedan hijos vivos\n\n");
	}
//hijos creados pares
	for(int i=1 ; i<NUM_HIJOS; i+=2){
		waitpid(PIDs[i],&estado,0);
		num_hijos--;
		printf("\nAcaba de finalizar el proceso %d\n", PIDs[i]);

		if(num_hijos>0)
			printf("Sólo me quedan %d hijos vivos\n", num_hijos);
		else
			printf("No me quedan hijos vivos\n\n");
	}

	return EXIT_SUCCESS;
}