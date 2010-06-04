import br.edu.fei.cc4641.bolsa.*;

/**
 * Implementa o executável da bolsa.
 */
public class Market {
    public static void main(String[] args) {
        Book.init();
        
        MarketServerConsole console = MarketServerConsole.instance();
        
        console.newMarketServer("Query",  7070, Protocol.PROTO_QUERYSTRING);
        console.newMarketServer("Serial", 7071, Protocol.PROTO_SERIALIZED);
    }

}
