#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

#define CANT_MENSAJES 1000

void imprimir(struct rusage *ru, time_t *t_total) {
    printf("Tiempo reloj: %ld microsegundos\n", *t_total);
    printf("Tiempo CPU sistema total: %ld microsegundos\n", ru->ru_stime.tv_usec);
    printf("Tiempo CPU usuario total: %ld microsegundos\n", ru->ru_utime.tv_usec);
    printf("Cantidad de Soft Page Faults: %ld \n", ru->ru_minflt);
    printf("Cantidad de Hard Page Faults: %ld \n", ru->ru_majflt);
    printf("Operaciones de entrada (en bloques): %ld \n", ru->ru_inblock);
    printf("Operaciones de salida (en bloques): %ld \n", ru->ru_oublock);
    printf("Mensajes IPC enviados: %ld \n", ru->ru_msgsnd);
    printf("Mensajes IPC recibidos: %ld \n", ru->ru_msgrcv);
}

int main()
{
    char f1_dir[] = "./file1";
    char f2_dir[] = "./file2";
    char msg[] = "B";
    char ans[sizeof(msg)];
    FILE *f1, *f2;
    struct stat st;
    off_t old_size;
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    f1 = fopen(f1_dir, "r");
    f2 = fopen(f2_dir, "a");

    old_size = 0;
    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        // printf("Esperando proceso A...\n");
        do {
            stat(f1_dir, &st);
            // Espera a que el proceso A escriba el archivo f1 o primera iteracion
        } while(old_size == st.st_size && old_size != 0);
        old_size = st.st_size;
        fread(ans, sizeof(char), 30, f1);
        // printf("Lectura completa\n");
        fprintf(f2 ,"%s", msg);
        fflush(f2);
    }

    fclose(f1);
    fclose(f2);

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    t_total = t_total / 1000 + 1000000*(fin.tv_sec - inicio.tv_sec); // convierte a microsegundos
    imprimir(&ru, &t_total);
    return 0;
}
