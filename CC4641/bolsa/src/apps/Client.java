package bolsa;

public class Client extends Thread {

    private Random r;
    private Broker broker;
    
    public Client(Broker br) {
        this.broker = br;
    }

    public void run() {
        while (true) {
            Order ord;
            
            if (wantBuy()) {
                String symbol   = getSymbol();
                float value     = getValue();
                float limit     = getLimit();
                ord = new BuyOrder(symbol, value, limit);
            }
            else {
                String symbol   = getSymbol();
                float quota     = getQuota();
                float limit     = getLimit();
                ord = new SellOrder(symbol, quota, limit);
            }
            
            Response res = broker.send(ord);
            
            printResponse(res);
            
            try {
                Thread.sleep(r.netxInt(3) * 1000);
            }
            catch (Exception e) {
                System.err.println(e);
            }
        }
    }
    
    private boolean wantBuy() {
        return r.nextInt(10) % 2;
    }
    
    private String getSymbol() {
        return "PETR1";
    }
    
    private float getValue() {
        return r.nextFloat();
    }
    
    private float getQuota() {
        return r.nextFloat();
    }
    
    private float getLimit() {
        return r.nextFloat();
    }
};
