#include <utils.h>

int main()
{
    int array[TAM_ARRAY];
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    long int sprom, uprom;
    struct rusage usage;
    pthread_t tid[CANT_PROCESOS];
    printf("------------ Caso 4 ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    inicializar(array);

    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pthread_create(&tid[i], NULL, threadEscritura, (void *) &usage);
        pthread_join(tid[i], NULL);
    }

    getrusage(RUSAGE_SELF, &usage);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    
    calcularTiempos(&inicio, &fin, &usage, &t_total, &t_prom, &sprom, &uprom);
    imprimir(&usage, &t_total, &t_prom, &sprom, &uprom);

    return 0;
}