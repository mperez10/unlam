#ifndef TP3EJ1_H
    #define TP3EJ1_H
    
    #define _GNU_SOURCE

    #define CANT_PROCESOS 1000
    #define TAM_ARRAY 10000

    #include <stdio.h>
    #include <stdlib.h>

    #include <time.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/resource.h>
    #include <sys/wait.h>
    #include <sys/time.h>

    struct th_args
    {
        int *array;
        struct rusage usage; // sin uso
    };

    void inicializar(int *array);

    void lectura(int *array);
    void *threadLectura(void *arg);
    void escritura(int *array);
    void *threadEscritura(void *arg);

    void calcularTiempos(struct timespec *inicio, struct timespec *fin, struct rusage *acum, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom);
    void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom);

    // sin uso:
    void acumUsage(struct rusage *acum, struct rusage *usage);
    void inicializarUsage(struct rusage *u);
#endif