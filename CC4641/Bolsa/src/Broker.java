import java.io.IOException;

import br.edu.fei.cc4641.bolsa.*;

public class Broker {
    public static void main(String[] args) {
        try {
            BrokerServer server = new BrokerServer(7080,"localhost", 7070);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
