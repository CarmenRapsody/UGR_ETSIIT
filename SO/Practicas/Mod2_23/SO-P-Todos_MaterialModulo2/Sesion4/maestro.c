/*
ejercicio5.c
maestro-esclavo
   - maestro: creara dos procesos esclavos y dividira el intervalo en dos subintervalos
   pasando cada uno como argumento a cada programa esclavo.
   El maestro ira reciviendo y mostrando uno a uno los primos calculados
   por los esclavos, en orden

   - esclavo:


  Compilacion:
    gcc -o maestro maestro.c


*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>



int main(int argc, char *argv[])
{

  /* Chck arguments */
	if(argc != 3) {
		printf("Error en los argumentos.\nEjerución: esclavo <intervalo_inf> <intervalo_sup>\n");
		exit(EXIT_FAILURE);
	}

	int fd1[2], fd2[2];
  int mitad, mitad_sup;	
	pid_t PID1, PID2;
  int num;
  int num_primos=0;
  
 
	mitad = (atoi(argv[1])+atoi(argv[2]))/2;
  mitad_sup = mitad+1;

  char extremo_inf1[5];
  char extremo_sup1[5];
  char extremo_inf2[5];
  char extremo_sup2[5];

  sprintf(extremo_inf1,"%d",atoi(argv[1]));
  sprintf(extremo_sup1,"%d",mitad);
  sprintf(extremo_inf2,"%d",mitad_sup);
  sprintf(extremo_sup2,"%d", atoi(argv[2]));

  //printf("Intervalo 1: %d %d\n",intervalo_inf[0], intervalo_sup[0]);
  //printf("Intervalo 2: %d %d\n",intervalo_inf[1], intervalo_sup[1]);
	

  //Creamos los cauces
  pipe(fd1); 
  pipe(fd2);


  //Creamos el hijo1
  if((PID1 = fork())< 0 ){
    perror("Error en fork1\n");
    exit(EXIT_FAILURE);
  }

  //hijo 1
  if(PID1==0){ //proceso hijo1
    close(fd1[0]); //cerramos el descriptor de lectura del proceso hijo1
    dup2(fd1[1], STDOUT_FILENO); //duplicamos el descriptor de escritura  del cauce1

    
    //ejecucion del esclavo, escribira los numeros primos del primer intervalo
    if(execl("./esclavo", "esclavo", extremo_inf1, extremo_sup1, NULL)<0){
      perror("Error en execl del hijo1");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

  }
  else{

    //hijo2
    if((PID2 = fork())< 0 ){
      perror("Error en fork1\n");
      exit(EXIT_FAILURE);
    }

    if(PID2==0){ //proceso hijo2
      close(fd2[0]); //cerramos el descriptor de lectura del proceso hijo2
      dup2(fd2[1], STDOUT_FILENO); //duplicamos el descriptor de escritura del cauce2

      //ejecucion del esclavo, escribira los numeros primos del segundo intervalo
      if(execl("./esclavo", "./esclavo",extremo_inf2, extremo_sup2, NULL)<0){
        perror("Error en execl del hijo2");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    }
    else{//proceso padre
      //Cierra los descriptores de escritura de los hijos
      close(fd1[1]); 
      close(fd2[1]);

      //Lee de los cauces
      while (read(fd1[0], &num, sizeof(int)) == sizeof(int)){
        printf("Cauce1 : ");
        printf("%d\n", num);
        num_primos++;
        
      }
      while (read(fd2[0], &num, sizeof(int)) == sizeof(int)){
        printf("Cauce2 : ");
        printf("%d\n", num);
        num_primos++;
      }
    }
  }

printf("Total de numeros primos: %d\n", num_primos);
return EXIT_SUCCESS;
}
