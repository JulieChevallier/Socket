#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 12345

struct sockaddr_in local;

int sock;
char mess[80];

void main()
{ 
    // Remplissage de la structure
    bzero(&local, sizeof(local)); 
    local.sin_family = AF_INET; 
    local.sin_port = htons(PORT); 
    local.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local.sin_zero),8);

    sock=socket(AF_INET, SOCK_DGRAM,0); // Création de la socket UDP (SOCK_DGRAM)
    bind(sock, (struct sockaddr *)&local, sizeof(struct sockaddr)) ; // 
    recvfrom (sock,mess,80,0,(struct sockaddr *)&local ,sizeof(struct sockaddr)); // accept() & read()
    printf ("le client me dit %s \n",mess);

    close(sock); // Fermeture de la socket
}

//Au lancement du serveur, un blocage à lieu jusqu'à ce que le client envoie un message.
//Si le client n'envoie pas de message, le serveur reste bloqué.
//Si le client envoie un message ou plusieurs, et que le serveur n'est pas en attente, le message ou les messages sont perdus.
//Si le client envoie un message et que le serveur est en attente, le message est reçu.