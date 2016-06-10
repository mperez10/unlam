#define _GNU_SOURCE

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>

#define CANT_PROCESOS 1000

void inicializar(int *array) {
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
        array[i] = rand();
}

void escritura(int *array) {
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
        array[i] *= ( rand() + 2);
}

void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long double *sprom, long double *uprom) {
    printf("Tiempo reloj: %ld nanosegundos\n", *t_total);
    printf("Tiempo reloj promedio: %ld nanosegundos\n", *t_prom);
    printf("Tiempo CPU sistema total: %ld microsegundos\n", ru->ru_stime.tv_usec);
    printf("Tiempo CPU usuario total: %ld microsegundos\n", ru->ru_utime.tv_usec);
    printf("Tiempo CPU sistema promedio: %Lf microsegundos\n", *sprom);
    printf("Tiempo CPU usuario promedio: %Lf microsegundos\n", *uprom);
    printf("Cantidad de Soft Page Faults: %ld \n", ru->ru_minflt);
    printf("Cantidad de Hard Page Faults: %ld \n", ru->ru_majflt);
    printf("Cantidad de señales recibidas: %ld \n", ru->ru_nsignals);
    printf("Cambios de contexto voluntarios: %ld \n", ru->ru_nvcsw);
    printf("Cambios de contexto involuntarios: %ld \n", ru->ru_nivcsw);
}

void inicializarUsage(struct rusage *u) {
        u->ru_stime.tv_usec = 0;
        u->ru_utime.tv_usec = 0;
        u->ru_minflt = 0;
        u->ru_majflt = 0;
        u->ru_nsignals = 0;
        u->ru_nvcsw = 0;
        u->ru_nivcsw = 0;
}

void *threadEscritura(void *arg) {
    struct rusage *ru = (struct rusage*)malloc(sizeof(struct rusage));
    int *array = (int *)arg;
    escritura(array);
    getrusage(RUSAGE_THREAD, ru);
    pthread_exit((void *)ru);
}

int caso4(int array[]) {
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    pthread_t tid[CANT_PROCESOS];
    long double sprom, uprom;
    struct rusage *usage, acum;
    void *returnValue;
    inicializarUsage(&acum);
    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);
    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pthread_create(&tid[i], NULL, threadEscritura, (void *) array);
        pthread_join(tid[i], &returnValue);
        usage = (struct rusage*)returnValue;
        acum.ru_stime.tv_usec += usage->ru_stime.tv_usec;
        acum.ru_utime.tv_usec += usage->ru_utime.tv_usec;
        acum.ru_minflt += usage->ru_minflt;
        acum.ru_majflt += usage->ru_majflt;
        acum.ru_nsignals += usage->ru_nsignals;
        acum.ru_nvcsw += usage->ru_nvcsw;
        acum.ru_nivcsw += usage->ru_nivcsw;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
            t_total += 1000000000;
    t_prom = ((long double)t_total) / CANT_PROCESOS;
    sprom = ((long double)acum.ru_stime.tv_usec) / CANT_PROCESOS;
    uprom = ((long double)acum.ru_utime.tv_usec) / CANT_PROCESOS;
    imprimir(&acum, &t_total, &t_prom, &sprom, &uprom);
    return 0;
}

int main() {
    int array[10000];
    inicializar(array);
    printf("------------ Caso 4 ------------\n");
    caso4(array);
    return 0;
}