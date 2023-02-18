class applic
{
    ExecutorService es;
    ServerSocket sockserv=null; // Socket du serveur
    DataInputStream in ; // Entrée
    DataOutputStream out; // Sortie
    byte mess[];

    public void main (String args[]) throws Exception {
        sockserv = new ServerSocket (1234); // Création de la socket
        
        try { 
            while (true){ 
                try { 
                    Socket sockcli = sockserv.accept(); // Attente d'une connexion avec un client
                    in = new DataInputStream (sockcli.getInputStream()); // Création d'un flux d'entrée
                    out = new DataOutputStream (sockcli.getOutputStream()); // Création d'un flux de sortie
                    in.read(mess,0,80); // Lecture
                    out.writeInt(mess.length()); // Ecriture
                    sockcli.close(); // Fermeture de la socket client
                }
                catch (IOException ex) { }
            }
        }
        finally { 
            try { 
                sockserv.close(); // Fermeture de la socket serveur
                es.shutdown();
            } 
            catch (IOException ex) { }
        }
    }
}

// 1. Un premier programme en Java

//2 -

// sockserv = new ServerSocket (1234);
// Correspond à :
// La préparation des champs d entête
// La création de la socket (sock)
// Nommage de la socket (bind)
// Mis en service de la socket (listen)

// Socket sockcli = sockserv.accept();
// Correspond à :
// Attente d'une connexion avec un client (accept)

// in = new DataInputStream (sockcli.getInputStream());
// out = new DataOutputStream (sockcli.getOutputStream());
// mess = nrw byte[80];
// in.read(mess,0,80);
// out.write(mess);
// Correspond à :
// Lecture (read)
// Ecriture (write)

// sockcli.close();
// sockserv.close();
// Correspond à :
// Fermeture de la socket (close)

//3 -

// L'attente de la connexion d'un client (accept)
// La lecture (read) puis l'écriture (write)

// 2. Le client Java

//1 -

// public class Client
// { 
//     Socket sockcli = null; // Socket du client
//     DataInputStream in; // Entrée
//     DataOutputStream out; // Sortie
//
//     public void main (String args[]) throws Exception { 
//         try { 
//             sockcli = new Socket (127.0.0.1, 1234); //Connexion au serveur
//             in = new DataInputStream (sockcli.getInputStream()); // Création d'un flux d'entrée
//             out = new DataOutputStream (sockcli.getOutputStream()); // Création d'un flux de sortie
//         }
//         catch (IOException ex){}
//         out.writeInt(mess.length()); // Ecriture de la taille du message
//         in.read(mess,0,taille); // Lecture du message
//
//         sockcli.close();
//     }
// }

// 2 -

// Modification faites pour la gestion de plusieurs clients

