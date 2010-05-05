package bolsa;

public class Response {

    private String  symbol;
    private int     operation;
    private float   quota;
    private float   value;
    private float   total;
    
    public Response(String s, int op, float q, float v, float t) {
        this.symbol     = s;
        this.operation  = op;
        this.quota      = q;
        this.value      = v;
        this.total      = t;
    }
};
