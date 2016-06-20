#include <utils.h>

void inicializar(int *array)
{
    srand(time(NULL));
    for (int i = 0; i < TAM_ARRAY; i++)
        array[i] = rand() % 100;
}

void lectura(int *array)
{
    int sum = 0;
    for(int i = 0; i < TAM_ARRAY; i++)
        sum += array[i];
}

void *threadLectura(void *arg)
{
    struct th_args *args = (struct th_args *)arg;
    lectura(&(args->array));
    pthread_exit(0);
}

void escritura(int *array)
{
    for (int i = 0; i < TAM_ARRAY; i++)
        array[i] *= rand() % 100 + 2;
}

void *threadEscritura(void *arg)
{
    struct th_args *args = (struct th_args *)arg;
    escritura(&(args->array));
    pthread_exit(0);
}

void calcularTiempos(struct timespec *inicio, struct timespec *fin, struct rusage *ru, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom)
{
    *t_total = fin->tv_nsec - inicio->tv_nsec; // nanosegundos
    *t_total = *t_total / 1000 + 1000000 * (fin->tv_sec - inicio->tv_sec); // convierte a microsegundos
    *t_prom = *t_total / CANT_PROCESOS; // se desprecia un valor infimo
    *sprom = ru->ru_stime.tv_usec / CANT_PROCESOS;
    *uprom = ru->ru_utime.tv_usec / CANT_PROCESOS;
}

void imprimir(struct rusage *ru, time_t *t_total, time_t *t_prom, long int *sprom, long int *uprom)
{
    printf("Tiempo reloj: %ld microsegundos\n", *t_total);
    printf("Tiempo reloj promedio: %ld microsegundos\n", *t_prom);
    printf("Tiempo CPU sistema total: %ld microsegundos\n", ru->ru_stime.tv_usec);
    printf("Tiempo CPU usuario total: %ld microsegundos\n", ru->ru_utime.tv_usec);
    printf("Tiempo CPU sistema promedio: %ld microsegundos\n", *sprom);
    printf("Tiempo CPU usuario promedio: %ld microsegundos\n", *uprom);
    printf("Cantidad de Soft Page Faults: %ld \n", ru->ru_minflt);
    printf("Cantidad de Hard Page Faults: %ld \n", ru->ru_majflt);
    printf("Cantidad de señales recibidas: %ld \n", ru->ru_nsignals);
    printf("Cambios de contexto voluntarios: %ld \n", ru->ru_nvcsw);
    printf("Cambios de contexto involuntarios: %ld \n", ru->ru_nivcsw);
}

void inicializarUsage(struct rusage *u)
{
    u->ru_stime.tv_usec = 0;
    u->ru_utime.tv_usec = 0;
    u->ru_minflt = 0;
    u->ru_majflt = 0;
    u->ru_nsignals = 0;
    u->ru_nvcsw = 0;
    u->ru_nivcsw = 0;
}

void acumUsage(struct rusage *acum, struct rusage *usage)
{
    acum->ru_stime.tv_usec += usage->ru_stime.tv_usec;
    acum->ru_utime.tv_usec += usage->ru_utime.tv_usec;
    acum->ru_minflt += usage->ru_minflt;
    acum->ru_majflt += usage->ru_majflt;
    acum->ru_nsignals += usage->ru_nsignals;
    acum->ru_nvcsw += usage->ru_nvcsw;
    acum->ru_nivcsw += usage->ru_nivcsw;
}