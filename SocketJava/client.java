public class Client
{ 
    Socket sockcli = null; // Socket du client
    DataInputStream in; // Entrée
    DataOutputStream out; // Sortie

    public void main (String args[]) throws Exception { 
        try { 
            sockcli = new Socket (127.0.0.1, 1234); //Connexion au serveur
            in = new DataInputStream (sockcli.getInputStream()); // Création d'un flux d'entrée
            out = new DataOutputStream (sockcli.getOutputStream()); // Création d'un flux de sortie
        }
        catch (IOException ex){}
        out.writeInt(mess.length()); // Ecriture de la taille du message
        in.read(mess,0,taille); // Lecture du message
        sockcli.close();
    }
}