package bolsa;

public class Broker {

    private Random r;

    public synchronized Response send(Order ord) {
        return exchange.negotiate(ord);
    }
    
    private Response negotiate(Order ord) {
        String symbol;
        int operation;
        float offer, limit, quota, value, total;
        
        symbol      = ord.getSymbol();
        operation   = ord.getOperation();
        limit       = ord.getLimit();
        
        if (ord.getOperation() == 1) {
            value       = ord.getValue();
            offer       = (float)r.nextInt((int)limit);
            
            if (offer > 0 && offer <= limit) {
                quota = value / offer;
                total = value;
            }
            else {
                quota = total = 0.0;
            }
        }
        else {
            quota       = ord.getQuota();
            offer       = (float)r.nextInt(2 * (int)limit);
            
            if (offer >= limit) {
                value = offer;
                total = value * quota;
            }
            else {
                value = total = 0.0;
            }
        }
        
        return new Response(symbol, operation, quota, offer, total);
    }
    
    private boolean operationDone() {
        return r.nextInt(10) % 2;
    }
};
