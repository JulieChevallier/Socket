#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define SERV "127.0.0.1"
#define PORT 12345

int port, sock, lg;
char mess[80];

struct sockaddr_in serv_addr; 
struct hostent *serveur;

int main(int argc, char const *argv[])
{
    lg = sizeof(struct sockaddr_in);
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serveur = gethostbyname(SERV);

    // bcopy(serveur, &serv_addr.sin_addr.s_addr, serveur->h_length);

    char* mess = "oui";
    socklen_t sock_len = sizeof(serv_addr);
    sendto(sock, mess, lg, 0, (struct sockaddr*)&serv_addr, sock_len);
    char* response =  malloc(sizeof(char)*1024);
    recvfrom(sock, response, lg, 0, (struct sockaddr*)&serv_addr, &sock_len);
    
    close(sock);
    free(response);
}