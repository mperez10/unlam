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

    void inicializar(int *array);
    // Inicializa todas las posiciones del array en 0.

    void lectura(int *array);
    // Suma los valores de todas las posiciones del array.

    void *threadLectura(void *arg);
    // Es la función de lectura que corre el thread cuando se crea.

    void escritura(int *array);
    // Multiplica el valor de cada posicion del array por
    // un número al azar.

    void *threadEscritura(void *arg);
    // Es la función de escritura que corre el thread cuando se crea.

    void calcularTiempos(struct timespec *inicio, struct timespec *fin, struct rusage *acum,
        time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom);
    // Calcula los tiempos.

    void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long int *sprom,
        long int *uprom);
    // Imprime los resultados en pantalla.

    // -- Funciones sin uso:
    void acumUsage(struct rusage *acum, struct rusage *usage);
    void inicializarUsage(struct rusage *u);
    // ---------------------

#endif