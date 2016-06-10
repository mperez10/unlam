#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

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
    char msg[] = "B", ans[sizeof(msg)];
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;
    sem_t *sem_x = sem_open("/sem_x", 0),
            *sem_y = sem_open("/sem_y", 0);
    int id = shmget((key_t)654, CANT_MENSAJES*sizeof(msg), IPC_CREAT | 0666);
    char (*vector)[sizeof(msg)] = (char *) shmat(id, NULL, 0);

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        sem_wait(sem_x);
        strcpy(ans, vector[i]);
        //printf("Se leyo %s en la posicion %d\n", ans, i);
        strcpy(vector[i], msg);
        //printf("Se escribio %s en la posicion %d\n", msg, i);
        sem_post(sem_y);
    }

    sem_close(sem_x);
    sem_close(sem_y);
    sem_unlink("/sem_x");
    sem_unlink("/sem_y");

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    imprimir(&ru, &t_total);

    return 0;
}
