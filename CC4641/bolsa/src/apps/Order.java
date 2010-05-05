package bolsa;

public class Order {
    protected String symbol;
    protected float value;
    protected float quota;
    protected float limit;
    protected int operation;
    
    protected Order(String symbol, float value, float quota, float limit,
                    float op) {
        this.symbol     = symbol;
        this.value      = value;
        this.quota      = quota;
        this.limit      = limit;
        this.operation  = op;
    }
};
