import br.edu.fei.cc4641.bolsa.*;

/**
 * Implementa o executável do broker
 */
public class Broker {
    public static void main(String[] args) {
        BrokerConsole console = BrokerConsole.instance();
        
        console.newBrokerInstance("Query", "localhost", 7070, 7080,
                Protocol.PROTO_QUERYSTRING);
        
        console.newBrokerInstance("Serial", "localhost", 7071, 7081,
                Protocol.PROTO_SERIALIZED);
    }
}
