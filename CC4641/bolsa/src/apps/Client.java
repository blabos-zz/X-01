package bolsa;


import java.util.Random;


public class Client extends Thread {

    private Random r;
    private Broker broker;
    private float balance;
    
    public Client(Broker br) {
        this.broker		= br;
        this.balance	= 10000;
        this.r			= new Random();
    }

    public void run() {
        while (true) {
            Order ord;
            
            if (wantBuy()) {
                String symbol   = getSymbol();
                float value     = 10 * getValue();
                float limit     = getLimit();
                ord = new BuyOrder(symbol, value, limit);
            }
            else {
                String symbol   = getSymbol();
                float quota     = getQuota();
                float limit     = 10 * getLimit();
                ord = new SellOrder(symbol, quota, limit);
            }
            
            Debug.print("New Order");
            Debug.print(ord.toXML());
            Response res = broker.send(ord);
            
            updateAccount(res);
            
            try {
                int period = (2 + r.nextInt(3)) * 1000;
                
                Debug.print("Going sleep for " + period + " msecs\n");
                
                Thread.sleep(period);
            }
            catch (Exception e) {
                System.err.println(e);
            }
        }
    }
    
    private void updateAccount(Response res) {
        if (res.getOperation() == 1) {
            Debug.print("Trade Result:");
            
            this.balance -= res.getTotal();
        }
        else {
            Debug.print("Sale Result:");
    	    this.balance += res.getTotal();
        }
        
        Debug.print(res.toXML());
        Debug.print("Current Balance: " + this.balance);
    }
    
    private boolean wantBuy() {
    	return (r.nextInt(10) % 2) == 0;
    }
    
    private String getSymbol() {
        return "PETR1";
    }
    
    private float getValue() {
        return 10 + r.nextFloat();
    }
    
    private float getQuota() {
        return 10 + r.nextFloat();
    }
    
    private float getLimit() {
        return 10 + r.nextFloat();
    }
};
