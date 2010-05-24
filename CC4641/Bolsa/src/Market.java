import br.edu.fei.cc4641.bolsa.*;

public class Market {
    public static void main(String[] args) {
        Book.init();
        
        @SuppressWarnings("unused")
        MarketServer server = new MarketServer(7070);
    }

}
