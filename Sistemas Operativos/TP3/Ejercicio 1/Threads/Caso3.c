#include <utils.h>

int main()
{
    int array[TAM_ARRAY];
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    pthread_t tid[CANT_PROCESOS];
    long int sprom, uprom;
    struct rusage *usage;
    struct th_args args;
    printf("------------ Caso 3 ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    inicializar(array);
    inicializarUsage(&(args.usage));

    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pthread_create(&tid[i], NULL, threadLectura, (void *) &args);
        pthread_join(tid[i], NULL);
    }

    getrusage(RUSAGE_SELF, &(args.usage));
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);

    calcularTiempos(&inicio, &fin, &(args.usage), &t_total, &t_prom, &sprom, &uprom);
    imprimir(&(args.usage), &t_total, &t_prom, &sprom, &uprom);
    
    return 0;
}