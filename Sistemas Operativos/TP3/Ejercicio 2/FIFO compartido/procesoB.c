#include <utils.h>

int main()
{
    char buffer[TAM_BUFFER];
    char msg[] = "B";
    char *fifo1 = "/tmp/fifo2";
    char *fifo2 = "/tmp/fifo1";
    int f1, f2;
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;
    printf("------------ Proceso B ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    mkfifo(fifo1, 0666);
    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        f2 = open(fifo2, O_RDONLY);
        read(f2, buffer, sizeof(buffer));
        //printf("Se recibio el mensaje: %s\n", buffer);
        close(f2);
        f1 = open(fifo1, O_WRONLY);
        write(f1, msg, sizeof(msg));
        //printf("Se envio el mensaje: %s\n", msg);
        close(f1);
        unlink(fifo1);
    }

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);

    calcularTiempos(&inicio, &fin, &t_total);
    imprimir(&ru, &t_total);

    return 0;
}
