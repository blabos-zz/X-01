package br.edu.fei.cc4641.bolsa;

abstract public class Operation {
    public static final int ERROR           = 0;
    public static final int BUY             = 1;
    public static final int SELL            = 2;
    public static final int ACCEPT          = 3;
    public static final int REJECT          = 4;
    public static final int INFO_REQUEST    = 5;
    public static final int INFO_RESPONSE   = 6;
    public static final int GREETING        = 7;
    public static final int INVALID         = 8;
    
    public static final String names[] = {
        "Error",
        "BuyOrder",
        "SellOrder",
        "Accept",
        "Reject",
        "MarketInfoRequest",
        "MarketInfoResponse",
        "Greeting",
        "Invalid",
    };

public static String asString(int operation) {
    String ret = "Error";
        
        try { ret = names[operation]; }
        catch (IndexOutOfBoundsException e) {}
        
        return ret;
    }
}
