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
#define TAM_ARRAY 1000000

void inicializar(int *array) {
    srand(time(NULL));
    for (int i = 0; i < TAM_ARRAY; i++)
        array[i] = rand();
}

void lectura(int *array) {
    int sum = 0;
    for(int i = 0; i < TAM_ARRAY; i++)
        sum += array[i];
}

void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long double *sprom, long double *uprom) {
    printf("Tiempo reloj: %ld microsegundos\n", *t_total);
    printf("Tiempo reloj promedio: %ld microsegundos\n", *t_prom);
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

void *threadLectura(void *arg) {
    struct rusage *ru = (struct rusage*)malloc(sizeof(struct rusage));
    int *array = (int *)arg;
    lectura(array);
    getrusage(RUSAGE_THREAD, ru);
    pthread_exit((void *)ru);
}

int caso3(int array[]) {
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
        pthread_create(&tid[i], NULL, threadLectura, (void *) array);
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
    t_total = t_total / 1000 + 1000000*(fin.tv_sec - inicio.tv_sec); // convierte a microsegundos
    t_prom = t_total / CANT_PROCESOS; // se desprecia un valor infimo
    sprom = acum.ru_stime.tv_usec / CANT_PROCESOS;
    uprom = acum.ru_utime.tv_usec / CANT_PROCESOS;
    imprimir(&acum, &t_total, &t_prom, &sprom, &uprom);
    return 0;
}

int main() {
    int array[TAM_ARRAY];
    inicializar(array);
    printf("------------ Caso 3 ------------\n");
    caso3(array);
    return 0;
}