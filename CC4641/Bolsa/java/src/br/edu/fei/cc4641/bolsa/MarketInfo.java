package br.edu.fei.cc4641.bolsa;

import java.util.HashMap;

public class MarketInfo {
    public HashMap<String, Share> data;
    
    public MarketInfo(Message msg) {
        data = new HashMap<String, Share>();
        fromMessage(msg);
    }
    
    public void fromMessage(Message msg) {
        String info = msg.asString("info");
        
        if (info == null) info = "";
        
        String shares[] = info.split(",");
        
        for (String sh : shares) {
            String fields[] = sh.substring(1, sh.length() - 1).split(";");
            data.put(fields[0], new Share(fields[0], fields[1], fields[2]));
        }
    }
    public void print() {
        for (Share s : data.values()) {
            System.out.printf("%10s%20.2f%20.2f\n",
            s.getSymbol(), s.getUnitValue(), s.getMaxQuotas());
        }
    }
}
