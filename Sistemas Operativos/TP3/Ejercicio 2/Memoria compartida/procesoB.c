#include <utils.h>

int main()
{
    char *msg = "B", ans;
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;
    sem_t *sem_x = sem_open("/sem_x", 0),
            *sem_y = sem_open("/sem_y", 0);
    int id = shmget((key_t)654, CANT_MENSAJES*sizeof(msg), IPC_CREAT | 0666);
    char *vector = (char *) shmat(id, NULL, 0);
    printf("------------ Proceso B ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        sem_wait(sem_x); // P(x)
        memcpy(&ans, &vector[i], sizeof(ans));
        //printf("Se leyo %c en la posicion %d\n", vector[i], i);
        memcpy(&vector[i], msg, sizeof(*msg));
        //printf("Se escribio %c en la posicion %d\n", vector[i], i);
        sem_post(sem_y); // V(x)
    }

    sem_close(sem_x);
    sem_close(sem_y);
    sem_unlink("/sem_x");
    sem_unlink("/sem_y");

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);

    calcularTiempos(&inicio, &fin, &t_total);
    imprimir(&ru, &t_total);

    return 0;
}
