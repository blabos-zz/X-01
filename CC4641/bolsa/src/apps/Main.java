import bolsa.Broker;
import bolsa.Client;


public class Main {
    public static void main(String args[]) {
        Broker broker = new Broker();

        Client c1 = new Client(broker, "Client 01");
        c1.start();
        
        Client c2 = new Client(broker, "Client 02");
        c2.start();
    }
};
