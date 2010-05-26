package br.edu.fei.cc4641.bolsa;

import java.util.HashMap;

@SuppressWarnings("serial")
public class Book extends HashMap<String, Share> {
    private static Book myself = null;
    
    public static Book instance() {
        if (myself == null) {
            init();
        }
        
        return myself;
    }
    
    private Book() {
        put("VALE5", new Share("VALE5",  43.50,   50000.00));
        put("PETR4", new Share("PETR4",  30.10,  600000.00));
        put("AMBV4", new Share("AMBV4", 172.00, 1000000.00));
        put("ELET6", new Share("ELET6",  14.30, 1000000.00));
        put("ITSA4", new Share("ITSA4",  14.80,      10.00));
        put("TAMM4", new Share("TAMM4",  27.49,     100.00));
        put("USIM5", new Share("USIM5",  90.30,  400000.00));
        put("CSNA3", new Share("CSNA3",  10.30,  200000.00));
        put("EMBR3", new Share("EMBR3",  20.10,  300000.00));
        put("ITAU4", new Share("ITAU4",  36.11,  250000.00));
    }
    
    public static void init() {
        myself = new Book();
    }
    
    public static boolean isAvaliable(String symbol) {
        return (
                myself.containsKey(symbol) &&
                myself.get(symbol).getMaxQuotas() > 0
        );
    }
    
    public static synchronized String getMarketInfo() {
        String res = "";
        
        for (Share s : Book.myself.values()) {
            res += "{" + s.getSymbol() + ";" + s.getUnitValue()
                + ";" + s.getMaxQuotas() + "},";
        }
        
        return res;
    }
}


class Share {
    private String symbol;
    private double unitValue;
    private double maxQuotas;
    
    public Share(String symbol, double value, double quotas) {
        this.setSymbol(symbol);
        this.setUnitValue(value);
        this.setMaxQuotas(quotas);
    }
    
    public Share(String symbol, String value, String quotas) {
        this.setSymbol(symbol);
        this.setUnitValue(Double.parseDouble(value));
        this.setMaxQuotas(Double.parseDouble(quotas));
    }
    
    public void decMaxQuotas(double value) {
        maxQuotas -= value;
    }
    
    public void incMaxQuotas(double value) {
        maxQuotas += value;
    }
    
    private void setSymbol(String symbol) {
        this.symbol = symbol;
    }
    
    public String getSymbol() {
        return symbol;
    }
    
    public void setUnitValue(double unitValue) {
        this.unitValue = unitValue;
    }
    
    public double getUnitValue() {
        return unitValue;
    }
    
    private void setMaxQuotas(double maxQuotas) {
        this.maxQuotas = maxQuotas;
    }
    
    public double getMaxQuotas() {
        return maxQuotas;
    }
}
