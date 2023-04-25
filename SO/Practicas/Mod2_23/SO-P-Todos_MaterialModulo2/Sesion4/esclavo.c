/*
ejercicio5.c
maestro-esclavo
   - maestro

   - esclavo: calculara los numeros primos que hay en el intervalo que se le
    pasa como argumento.
    
    COmpilar:
            gcc -o esclavo esclavo.c -lm ( -lm para enlaza la libreria)


*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int  esPrimo(int k){
	int es_primo= 1;

	for (int i=2; i<= sqrt(k) && es_primo; i++){
		if(k%i == 0) es_primo = 0;

	}
	return es_primo;
}

int main(int argc, char *argv[]){

    int intervalo_inf, intervalo_sup;

    /* Check arguments */
    if(argc != 3) {
		printf("Error en los argumentos.\nEjerución: esclavo <intervalo_inf> <intervalo_sup>\n");
		exit(EXIT_FAILURE);
	}

    intervalo_inf = atoi(argv[1]);
	intervalo_sup = atoi(argv[2]);

    for (int i=intervalo_inf; i<=intervalo_sup; i++){
        if(esPrimo(i)) write(STDOUT_FILENO, &i, sizeof(int));
    }
    
    exit(EXIT_SUCCESS);

}
