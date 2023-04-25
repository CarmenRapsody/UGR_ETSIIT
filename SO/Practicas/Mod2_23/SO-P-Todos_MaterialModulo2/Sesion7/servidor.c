#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define tamano 1024
#define longnombre 50

void proxy (int pid){
    char *nombre;
    int fd;

    // Genero el nombre
    sprintf(nombre, "/tmp/fifo.%d", pid);

    // Creo un FIFO
    mkfifo(nombre, 0777);

    // Abro el FIFO
    fd = open(nombre, O_RDWR);
    if (fd < 0){
        perror("Error en write\n");
        exit(EXIT_FAILURE);
    }

    // Redirijo la entrada estandar al archivo
    dup2(fd, STDIN_FILENO);

    // Ejecuto el proxy
    execlp("./proxy", "./proxy", NULL);

    // Si no se ejecuta el proxy
    perror("Fallo en execlp\n");
    exit(EXIT_FAILURE);
}



int main(int argc, char **argv){
    // Redirigimos STDERR_FILENO a STDOUT_FILENO
    dup2(STDOUT_FILENO, STDERR_FILENO);
    //dup2(1,2);

    int buf [tamano];
    int dfifos, dfifoe, numbytes;

    char nombrefifoe[longnombre], nombrefifos[longnombre];

    setbuf(stdout, NULL);
    
    if(argc != 2){
        printf("Uso: %s <nombre_fifo>\n", argv[0]);
        exit(1);
    }

    // Compone los nombres de los FIFOs conocidos a partir del parametro,
    // unp de entrada y otro de salida (desde el punto de vista del servidor)
    sprintf(nombrefifoe, "%se", argv[1]);
    sprintf(nombrefifos, "%ss", argv[1]);

    // Borramos los archivos fifo por si existieran previamente
    unlink(nombrefifoe);
    unlink(nombrefifos);

    int pid;

    umask(0);

    // Creamos un cauce con nombre para la entrada
    if (mkfifo(nombrefifoe, 0777) == -1){
        perror("Error en mkfifo\n");
        exit(EXIT_FAILURE);
    }

    // Creamos un cauce con nombre para la salida
    if (mkfifo(nombrefifos, 0777) == -1){
        perror("Error en mkfifo\n");
        exit(EXIT_FAILURE);
    }

    printf ("Crear cauce salida\n");

    // Abrimos los cauces
    dfifos = open(nombrefifos, O_RDWR);
    dfifoe = open(nombrefifoe, O_RDWR);

    printf ("Cauces creados\n");

    numbytes = read(dfifos, buf, sizeof(buf));

    while(numbytes > 0){
        printf("Leyendo fifo salida\n");
        pid = fork();
        if (pid == 0)       // Hijo
            proxy(getpid());
        else if (pid > 0){  // Padre
            printf("El pid del padre es %f\n", pid);
            if (write(dfifoe, &pid, sizeof(int)) < 0){
                perror("Error en write\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid == -1){
            perror("Fallo en el fork\n");
            exit(EXIT_FAILURE);
        }
        numbytes = read(dfifos, buf, sizeof(buf));
    }

    if (numbytes == -1){
        perror("Error en read\n");
        exit(EXIT_FAILURE);
    }

    pid = wait(NULL);
    while (pid > 0) pid = wait(NULL);

    // Si hay error ignoramos que hay mas hijos a los que esperar
    if (pid == -1 && errno != ECHILD){
        perror("Fallo en wait\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}