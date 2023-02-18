#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>


#define PORT 12345 //Port de communication
#define SERVEUR "127.0.0.1" //Ip ciblé

struct hostent *server;
struct sockaddr_in serv_addr; // champ d'entête socket a envoyer

int sock, lg;
char mess[128];

void createSocket()
{
    server = gethostbyname(SERVEUR); // récupération de l'adresse IP
    bzero(&serv_addr, sizeof(serv_addr)); // mise a zero de la zone adresse
    serv_addr.sin_family = AF_INET; // famille d adresse internet
    serv_addr.sin_port = htons(PORT); // numéro de port
    serv_addr.sin_addr.s_addr = *(long *)server->h_addr; // types d'adresses prises en charge
    bzero(&(serv_addr.sin_zero),8); // fin de remplissage
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //création socket du serveur mode TCP/IP
        printf("Erreur (Creation socket) : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char* argv[])
{
    mess[0] = '\0';
    createSocket();
    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))){
        printf("%i fd socket", sock);
        printf("Erreur (Connection) : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while(strncmp("fin",mess,3) != 0)
    {
        printf("Saisir message : ");
        fflush(stdout);
        lg = read(0,mess,128);
        mess[lg] = '\0';
        send(sock,mess,lg,0);
        lg = recv(sock,mess,128,0);
        mess[lg] = '\0';
        printf("Message Recu : %s\n",mess);
    }
    close(sock);
}


//gcc serveur.c -o serveur
//gcc client.c -o client
//./serveur
//telnet 127.0.0.1 12345 ou ./client