#include <utils.h>

int main()
{
    char msg[] = "B", ans[sizeof(msg)];
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;
    sem_t *sem_x = sem_open("/sem_x", 0),
            *sem_y = sem_open("/sem_y", 0);
    int id = shmget((key_t)654, CANT_MENSAJES*sizeof(msg), IPC_CREAT | 0666);
    char (*vector)[sizeof(msg)] = (char *) shmat(id, NULL, 0);
    printf("------------ Proceso B ------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    for(int i = 0; i < CANT_MENSAJES; i++)
    {
        sem_wait(sem_x);
        strcpy(ans, vector[i]);
        //printf("Se leyo %s en la posicion %d\n", ans, i);
        strcpy(vector[i], msg);
        //printf("Se escribio %s en la posicion %d\n", msg, i);
        sem_post(sem_y);
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
