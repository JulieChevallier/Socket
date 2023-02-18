#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>

#define PORT 12345

struct sockaddr_in local; // champs d entete local
struct sockaddr_in distant; // champs d entete distant

int sock_s, sock_c, lg;
char mess[80];

void createSocket()
{
    // preparation des champs d entete
    bzero(&local, sizeof(local)); // mise a zero de la zone adresse
    local.sin_family = AF_INET; // famille d adresse internet
    local.sin_port = htons(PORT); // numero de port
    local.sin_addr.s_addr = INADDR_ANY; // types d adresses prises en charge
    bzero(&(local.sin_zero),8); // fin de remplissage
    lg = sizeof(struct sockaddr_in);
    sock_s = socket(local.sin_family,SOCK_STREAM,0); // Creation sock_s en mode TCP/IP
    if(sock_s == -1){
        printf("Erreur (Creation socket) : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if(bind(sock_s,(struct sockaddr*)&local,sizeof(struct sockaddr_in))){
        printf("Erreur (Nommage) : %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    } // Nommage sock_s

}

void gestionClient()
{
        strcpy(mess,"");
        while (strncmp(mess,"fin\0",3)!=0)
        { 
            int nb_read = read(sock_c,mess,80);
            if(sock_c == -1){
                printf("Client déconnecter : %s",strerror(errno));
                exit(EXIT_FAILURE);
            }
            mess[nb_read] = '\0';
            printf ("Le client me dit %s \n",mess);
            printf("Saisir message : ");
            fflush(stdout);
            nb_read = read(0,mess,80);
            mess[nb_read] = '\0';
            write(sock_c,mess,nb_read);
            

        }
        printf("Connection terminé ");
        exit(0);
}


int main(int argc, char* argv[])
{
    createSocket(); //creation de la sock_s
    
    if(listen(sock_s,6)){
        printf("Erreur (Mise en ecoute) : %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    while(1) // boucle sans fin pour la gestion des connexions
    {
        sock_c = accept(sock_s,(struct sockaddr*)&distant,&lg); // attente connexion client
        if(sock_c == -1){
            printf("Erreur connection client");
        }
        else{
            printf ("Client connecté ! \n");
            int pid = fork();
            if(pid == 0){
                gestionClient();
            }   
        }
        close(sock_c); // fermeture de la sock_c
    }
    return 0;
}