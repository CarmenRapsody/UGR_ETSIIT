//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[])
{
int var;
pid_t pid;

var=88;
//escribe en el lfichero pantalla, a partir de la dir de memoria a la que apunte buf, 
// y escribe tantos bytes como sean sizeof(buf)+1
//es mas recomendable  usar: strlen(buf)*sizeof(char)
if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
	perror("\nError en write");
	exit(EXIT_FAILURE);
}
//(1)if(setvbuf(stdout,NULL,_IONBF,0)) { habilita el buffering de salida
//	perror("\nError en setvbuf");
//}
//veremos todos los mensajes sobre la marcha

printf("\nMensaje previo a la ejecución de fork");

//fintf(stdout) mas recomendable para sacar informacion de pantalla, mas fiable
//printf si no se completa su buffer no sale por pantalla
if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  
	//proceso hijo ejecutando el programa
	global++;
	var++;
} else  //proceso padre ejecutando el programa
	sleep(1);		
printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
exit(EXIT_SUCCESS);
}
