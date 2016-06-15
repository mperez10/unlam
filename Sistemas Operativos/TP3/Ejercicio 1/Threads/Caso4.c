#include <utils.h>

int main() {
    int array[TAM_ARRAY];
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    pthread_t tid[CANT_PROCESOS];
    long int sprom, uprom;
    struct rusage *usage, acum;
    void *returnValue;
    printf("------------ Caso 4 ------------\n");

    inicializar(array);
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
    
    calcularTiempos(&inicio, &fin, &acum, &t_total, &t_prom, &sprom, &uprom);
    imprimir(&acum, &t_total, &t_prom, &sprom, &uprom);

    return 0;
}