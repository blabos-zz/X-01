import bolsa.Broker;
import bolsa.Client;


public class Main {
    public static void main(String args[]) {
        Broker broker = new Broker();

        Client c1 = new Client(broker);
        c1.start();
    }
};
