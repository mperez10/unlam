#ifndef TP3EJ1_H
    #define TP3EJ1_H
    
    #define _GNU_SOURCE

    #define CANT_PROCESOS 1000
    #define TAM_ARRAY 1000000

    #include <stdio.h>
    #include <stdlib.h>

    #include <time.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/resource.h>
    #include <sys/wait.h>
    #include <sys/time.h>

    void inicializar(int *array);
    void inicializarUsage(struct rusage *u);

    void lectura(int *array);
    void *threadLectura(void *arg);
    void escritura(int *array);
    void *threadEscritura(void *arg);

    void calcularTiempos(struct timespec *inicio, struct timespec *fin, struct rusage *acum, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom);
    void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom);
#endif