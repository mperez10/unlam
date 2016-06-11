#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <time.h>
#include <sys/resource.h>

#define SERVER_PORT 5000
#define SERVER_IP "127.0.0.1"
#define CANT_MENSAJES 1000
#define TAM_BUFFER 100

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

void setClientAddr(struct sockaddr_in *client_addr, const char *ip, int port)
{
    client_addr->sin_family = AF_INET;
    client_addr->sin_port = htons(port);
    client_addr->sin_addr.s_addr = inet_addr(ip);
    memset(&(client_addr->sin_zero), 0, sizeof(client_addr->sin_zero));
};

int main(int argc, char *argv[])
{
    int server_socket;
    char buffer[TAM_BUFFER];
    struct sockaddr_in server_addr;
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        printf("No se pudo crear el socket\n");
        return 1;
    }

    setClientAddr(&server_addr, SERVER_IP, SERVER_PORT);
    if(connect(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("No se pudo conectar al servidor\n");
        return 1;
    }

    // Conexion lista

    for (int i = 0; i < CANT_MENSAJES; ++i)
    {
        memset(buffer, 0, sizeof(buffer));
        recv(server_socket, buffer, sizeof(buffer), 0);
        //printf("Recibido: %s\n", buffer);
        send(server_socket, "C\n", 1, 0);
        //printf("Enviado\n");
    }

    close(server_socket);

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    t_total = t_total / 1000 + 1000000*(fin.tv_sec - inicio.tv_sec); // convierte a microsegundos
    imprimir(&ru, &t_total);
    return 0;
}
