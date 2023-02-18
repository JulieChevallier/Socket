#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define SERV "127.0.0.1"
#define PORT 12345 

struct sockaddr_in serv_addr; // Champ d'entête socket a envoyer
struct hostent *server;

int sock;
char mess[80];

int main()
{ 
    sock = socket(AF_INET, SOCK_DGRAM, 0); //Création de la socket UDP (SOCK_DGRAM)

    server = gethostbyname(SERV);
    // Remplissage de la structure
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(PORT);

    printf ("Question : "); gets(mess);
    sendto(sock,mess,80,0,(struct sockaddr *)&serv_addr,sizeof(serv_addr)); // connect() & write()
    printf ("Message envoyé \n ");

    close (sock); // Fermeture de la socket
}

//Au lancement du client, un message est envoyé au serveur.
//Il n'y a pas de blocage.
//Si le serveur n'est pas en attente, le message est perdu.
//Si le serveur est en attente, le message est reçu.