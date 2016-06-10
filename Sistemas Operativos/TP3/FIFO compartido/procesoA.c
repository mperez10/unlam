#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

#define CANT_MENSAJES 1000
#define TAM_BUFFER 100

void imprimir(struct rusage *ru, time_t *t_total) {
    printf("Tiempo reloj: %ld nanosegundos\n", *t_total);
    printf("Tiempo CPU sistema total: %ld microsegundos\n", ru->ru_stime.tv_usec);
    printf("Tiempo CPU usuario total: %ld microsegundos\n", ru->ru_utime.tv_usec);
    printf("Cantidad de Soft Page Faults: %ld \n", ru->ru_minflt);
    printf("Cantidad de Hard Page Faults: %ld \n", ru->ru_majflt);
    printf("Operaciones de entrada (en bloques): %ld \n", ru->ru_inblock);
    printf("Operaciones de salida (en bloques): %ld \n", ru->ru_oublock);
    printf("Mensajes IPC enviados: %ld \n", ru->ru_msgsnd);
    printf("Mensajes IPC recibidos: %ld \n", ru->ru_msgrcv);
}

int main()
{
    char buffer[TAM_BUFFER];
    char msg[] = "A";
    char *fifo1 = "/tmp/fifo1";
    char *fifo2 = "/tmp/fifo2";
    int f1, f2;
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    mkfifo(fifo1, 0666);
    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        f1 = open(fifo1, O_WRONLY);
        write(f1, msg, sizeof(msg));
        //printf("Se envio el mensaje: %s\n", msg);
        close(f1);
        unlink(fifo1);
        f2 = open(fifo2, O_RDONLY);
        read(f2, (void *) buffer, sizeof(buffer));
        //printf("Se recibio el mensaje: %s\n", buffer);
        close(f2);
    }

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    imprimir(&ru, &t_total);

    return 0;
}
