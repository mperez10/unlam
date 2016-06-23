#include <utils.h>

int main()
{
    int array[TAM_ARRAY];
    struct timespec inicio, fin;
    time_t t_total, t_prom;
    long int sprom, uprom;
    struct rusage usage;
    pid_t pid[CANT_PROCESOS];
    printf("------------ Caso 1 ------------\n");
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    inicializar(array);
    
    for (int i = 0; i < CANT_PROCESOS; i++)
    {
        pid[i] = fork();
        // Se crea un nuevo proceso igual
        // (solo cambia el valor de pid[i])
        if (pid[i] == 0)
        {
            // Proceso Hijo: Realiza las operaciones y finaliza
            lectura(array);
            return 0;
        }
        else if (pid[i] == -1)
        {
            printf("Error creando proceso\n");
            return 1;
        }
        else
        {
            // Proceso Padre: Espera a los hijos que terminen uno por uno
            // en cada iteración del ciclo for.
            wait(NULL);
        }
    }

    getrusage(RUSAGE_SELF, &usage);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    
    calcularTiempos(&inicio, &fin, &usage, &t_total, &t_prom, &sprom, &uprom);
    imprimir(&usage, &t_total, &t_prom, &sprom, &uprom);

    return 0;
}