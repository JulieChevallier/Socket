#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define SERV "193.27.194.177" // IP Google
#define PORT 80 // Port d’écoute serveur


struct sockaddr_in serv_addr; // Champ d'entête socket a envoyer
struct hostent *server;

int sock, lg;
char mess[1000];

createSocket()
{ 
    server = gethostbyname(SERV); // adresse IP
    if (!server){
        fprintf(stderr, "Erreur (Serveur) \"%s\"\n", SERV);exit(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0); // Création socket locale
    bzero(&serv_addr, sizeof(serv_addr)); // Préparation du champs d'entête
    serv_addr.sin_family = AF_INET; // Le type d’adresses
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(PORT); // Port de connexion du serveur
}

main()
{
    createSocket(); // Création de la socket

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur (Connexion) :");
        exit(1);
    }
    printf ("Serveur connecté !\n");
    strcpy(mess,"GET / \n"); // Envoie de la requête,
    write (sock, mess, strlen(mess));

    lg = read (sock, mess, 80); //Lecture de la réponse (80 caractères)
    printf("%s",mess);
    while (lg == 80){ //Boucle de lecture (80 caractères)
        lg=read (sock, mess, 80); 
        printf("%s",mess);
    }
    printf("\n");

    close (sock); // Fermeture de la socket
}
