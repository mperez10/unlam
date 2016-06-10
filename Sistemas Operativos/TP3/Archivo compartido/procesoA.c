#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

#define CANT_MENSAJES 1000

void imprimir(struct rusage *ru, time_t *t_total) {
	printf("Tiempo reloj: %ld nanosegundos\n", *t_total);
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
    char f1_dir[] = "/home/franco/Proyectos/Console/shared_file/file1";
    char f2_dir[] = "/home/franco/Proyectos/Console/shared_file/file2";
    char msg[] = "A";
    char ans[sizeof(msg)];
    FILE *f1, *f2;
    struct stat st;
    off_t old_size;
    struct timespec inicio, fin;
	time_t t_total;
	struct rusage ru;

	clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

	// Se crean y/o vacian los archivos
	f1 = fopen(f1_dir, "w");
	fclose(f1);
    f2 = fopen(f2_dir, "w");
    fclose(f2);

    f1 = fopen(f1_dir, "a");
    f2 = fopen(f2_dir, "r");

    old_size = 0;
    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        fprintf(f1 ,"%s", msg);
        fflush(f1);
        // printf("Esperando proceso B...\n");
        do {
            stat(f2_dir, &st);
            // Espera a que el proceso B escriba el archivo f2
        } while(old_size == st.st_size);
        old_size = st.st_size;
        fread(ans, sizeof(char), 30, f2);
        // printf("Lectura completa\n");
    }

    fclose(f1);
    fclose(f2);

    remove(f1_dir);
    remove(f2_dir);

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    imprimir(&ru, &t_total);
    return 0;
}
