import br.edu.fei.cc4641.bolsa.*;

public class Broker {
    public static void main(String[] args) {
        try {
            BrokerServer server = new BrokerServer(7080,"localhost", 7070);
            server.start();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
