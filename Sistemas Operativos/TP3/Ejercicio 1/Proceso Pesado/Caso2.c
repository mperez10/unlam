#include <utils.h>

int main()
{
    int array[TAM_ARRAY];
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    long int sprom, uprom;
    struct rusage usage;
    pid_t pid[CANT_PROCESOS];
    printf("------------ Caso 2 ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    inicializar(array);

    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            escritura(array);
            return 0;
        }
        else if (pid[i] == -1)
        {
            printf("Error creando proceso\n");
            return 1;
        }
        else
        {
            wait(NULL);
        }
    }

    getrusage(RUSAGE_SELF, &usage);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);

    calcularTiempos(&inicio, &fin, &usage, &t_total, &t_prom, &sprom, &uprom);
    imprimir(&usage, &t_total, &t_prom, &sprom, &uprom);

    return 0;
}