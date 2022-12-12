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

#define SERV "127.0.0.1"
#define PORT 12345
int port, sock;
char mess[80];

struct sockaddr_in serv_addr; 
struct hostent *serveur;

void creer_socket() {
// preparation des champs d entete

    port = PORT;
    serveur = gethostbyname(SERV);
    if (!serveur){fprintf(stderr, "Problème serveur \"%s\"\n",SERV);exit(1);}

    sock=socket(AF_INET, SOCK_STREAM, 0); // creation socket du serveur mode TCP/IP
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(serveur->h_addr, &serv_addr.sin_addr.s_addr,serveur->h_length);
    serv_addr.sin_port = htons(port);
}

int main() {
    // création socket
    creer_socket();
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (strncmp(mess, "fin", 3) != 0) {
        printf("Entre ton texte : ");
        gets(mess);
        if(strncmp(mess, "fin",3) == 0){
            write(sock,"end", 80);
            printf("Fin connexion\n");
            close(sock);
            exit(0);
        }
        write(sock, mess, 80);
        read(sock, mess, 80);
        printf("Réponse du seveur : %s\n", mess);
    }
    close(sock);

    return 0;
}