#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define PORT 12345

int sock, lg;

struct sockaddr_in local; // champs d entete local
struct sockaddr_in distant; // champs d entete distant

int main(int argc, char const *argv[])
{
    lg = sizeof(struct sockaddr_in);
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&local, sizeof(local)); // mise a zero de la zone adresse
    local.sin_family = AF_INET; // famille d adresse internet
    local.sin_port = htons(PORT); // numero de port
    local.sin_addr.s_addr = INADDR_ANY; // types d adresses prises en charge
    bzero(&(local.sin_zero), 8); // fin de remplissage

    bind(sock, (struct sockaddr *)&local, lg); // nommage de la socket

    char* mess, response;
    int read;

    mess = malloc(sizeof(char)*1024);
    socklen_t len_sock = sizeof(struct sockaddr_in);
    recvfrom(sock, mess, 1024, 0, (struct sockaddr *)&distant, &len_sock); //reçoit la requête du client et l'écrit dans l'entête
    response = process(mess);
    read = sendto(sock, response, lg, 0, (struct sockaddr*)&distant, sizeof(distant));

    free(mess);
}
