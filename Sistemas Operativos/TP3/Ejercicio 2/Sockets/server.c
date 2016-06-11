#include <netdb.h>      
#include <stdio.h>  
#include <string.h>     
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/resource.h>

#define PORT 5000
#define MAX_QUEUE 5
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

void setServerAddr(struct sockaddr_in *server_addr, int port)
{
    server_addr->sin_family = AF_INET; // AF_INET es la familia de IPs IPv4
    server_addr->sin_port = htons(port); // Convierte el puerto (protocolo)
    server_addr->sin_addr.s_addr = INADDR_ANY; // Acepta comunicacion a cualquier IP--Especifico: inet_addr("127.0.0.1")
    memset(&(server_addr->sin_zero), 0, sizeof(server_addr->sin_zero));
};

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int server_socket;
    int client_socket;
    socklen_t client_addr_len;  
    char buffer[TAM_BUFFER];
    struct timespec inicio, fin;
    time_t t_total;
    struct rusage ru;
    int pts = 0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &inicio);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) // retorna -1 cuando no puede crear el socket
        return 1;

    setServerAddr(&server_addr, PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    listen(server_socket, MAX_QUEUE);
    client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len);

    // Conexion lista

    for (int i = 0; i < CANT_MENSAJES; ++i)
    {
        send(client_socket, "S\n", 1, 0);
        //printf("Enviado\n");
        memset(buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);
        //printf("Recibido: %s\n", buffer);
    }

    close(client_socket);
    close(server_socket);

    getrusage(RUSAGE_SELF, &ru);
    clock_gettime(CLOCK_MONOTONIC_RAW, &fin);
    t_total = fin.tv_nsec - inicio.tv_nsec;
    if (t_total < 0)
        t_total += 1000000000;
    t_total = t_total / 1000 + 1000000*(fin.tv_sec - inicio.tv_sec); // convierte a microsegundos
    imprimir(&ru, &t_total);
    return 0; 
};
