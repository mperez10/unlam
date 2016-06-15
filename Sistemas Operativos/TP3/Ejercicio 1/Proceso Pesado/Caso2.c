#include <utils.h>

int main() {
    int array[TAM_ARRAY];  
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    long int sprom, uprom;
    struct rusage usage, acum;
    pid_t pid[CANT_PROCESOS];
    printf("------------ Caso 2 ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    inicializar(array);

    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pid[i] = fork();
        if (pid[i] == 0) // Proceso Hijo
        {
            escritura(array);
            i = CANT_PROCESOS;
            return 0;
        }
        else if (pid[i] == -1)
        {
            printf("Error creando proceso\n");
            return 1;
        }
    }

    // Continua el proceso Padre

    inicializarUsage(&acum);
    for (int j = 0; j < CANT_PROCESOS; j++)
    {
        wait3(NULL, 0, &usage);
        acum.ru_stime.tv_usec += usage.ru_stime.tv_usec;
        acum.ru_utime.tv_usec += usage.ru_utime.tv_usec;
        acum.ru_minflt += usage.ru_minflt;
        acum.ru_majflt += usage.ru_majflt;
        acum.ru_nsignals += usage.ru_nsignals;
        acum.ru_nvcsw += usage.ru_nvcsw;
        acum.ru_nivcsw += usage.ru_nivcsw;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);

    calcularTiempos(&inicio, &fin, &acum, &t_total, &t_prom, &sprom, &uprom);
    imprimir(&acum, &t_total, &t_prom, &sprom, &uprom);

    return 0;
}