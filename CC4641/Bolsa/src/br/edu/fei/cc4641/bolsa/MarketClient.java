package br.edu.fei.cc4641.bolsa;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class MarketClient extends MarketThread {
    private Socket client           = null;
    private PrintWriter netOut      = null;
    private BufferedReader netIn    = null;
    
    public MarketClient(Socket client) throws IOException {
        this.client = client;
        
        netOut
            = new PrintWriter(this.client.getOutputStream(), true);
        
        netIn
            = new BufferedReader(
                    new InputStreamReader(
                            this.client.getInputStream()));
        
        start();
    }
    
    public void run() {
        while (!canStop()) {
            Message msg = null;
            Message res = null;
            
            msg = getMsg();
            
            if (msg == null) {
                netOut.close();
                return;
            }
            
            System.out.println(msg.toXML());
            
            switch (msg.asInt("operation")) {
                case Operation.BUY:
                    res = procBuy(msg);
                    break;
                case Operation.SELL:
                    res = procSell(msg);
                    break;
                case Operation.INFO_REQUEST:
                    res = procInfo(msg);
                    break;
                case Operation.GREETING:
                    res = procGreeting(msg);
                    break;
                default:
                    res = procOperNotFound(msg);
            }
            
            System.out.println(res.toXML());
            netOut.println(res.toStr());
        }
    }

    private Message getMsg() {
        Message msg = null;
        try {
            String line = netIn.readLine();
            if (line == null) {
                throw new IOException("Connection closed by peer");
            }
            
            msg = new Message(line);
            
            msg.checkHeader();
        } catch (IOException e) {
            System.out.println(e.getMessage()
                    + ". Closing client connection");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            msg = new Message();
            msg.put("operation", Operation.ERROR);
            msg.put("error", e.getMessage());
            netOut.println(msg.toStr());
            msg = null;
        }
        
        return msg;
    }

    private Message procGreeting(Message msg) {
        Message resp    = new Message();
        
        String clientId = msg.asString("clientId");
        
        try {
            String greeting = "";
            
            msg.ckeckGreeting();
            
            System.out.println(msg.toXML());
            
            greeting += "Welcome " + clientId + "! ";
            greeting += "I'm Market v 2.0. ";
            greeting += "Messages Supported: ";
            for (String name : Operation.names) {
                greeting += name + ", ";
            }
            greeting = greeting.substring(0, greeting.length() - 2) + ".";
            
            resp.put("clientId",    clientId);
            resp.put("operation",   Operation.GREETING);
            resp.put("greet",       greeting);
        }
        catch (Exception e) {
            System.err.println(e.getMessage());
            
            resp.put("clientId",    clientId);
            resp.put("operation",   Operation.ERROR);
            resp.put("error",       e.getMessage());
        }
        
        return resp;
    }

    private Message procInfo(Message msg) {
        Message resp    = new Message();
        
        String clientId = msg.asString("clientId");
        
        resp.put("clientId", clientId);
        
        try {
            msg.ckeckInfoRequest();
            
            resp.put("clientId",    clientId);
            resp.put("operation",   Operation.INFO_RESPONSE);
            resp.put("info",        Book.getMarketInfo());
        }
        catch (Exception e) {
            resp.put("clientId",    clientId);
            resp.put("operation",   Operation.ERROR);
            resp.put("info",        e.getMessage());
        }
        
        return resp;
    }

    private Message procOperNotFound(Message msg) {
        Message resp    = new Message();
        
        String clientId = msg.asString("clientId");
        int operation   = msg.asInt("operation");
        
        resp.put("clientId",    clientId);
        resp.put("operation",   Operation.ERROR);
        resp.put("error",       "Operation '" + operation
                                + "' was not supported");
        
        return resp;
    }

    private Message procSell(Message msg) {
        Message resp    = new Message();
        
        String clientId = msg.asString("clientId");
        String symbol   = msg.asString("symbol");
        double quotas   = msg.asDouble("quotas");
        double limit    = msg.asDouble("limit");
        
        resp.put("clientId", clientId);
        resp.put("symbol",   symbol);
        
        try {
            msg.checkSell();
            
            Book book = Book.instance();
            synchronized (book) {
                if (book.containsKey(symbol)) {
                    Share share         = book.get(symbol);
                    double unitValue    = share.getUnitValue();
                    
                    if (unitValue >= limit) {
                        double total = quotas * unitValue;
                        
                        share.incMaxQuotas(quotas);
                        
                        resp.put("quotas",      quotas);
                        resp.put("value",       unitValue);
                        resp.put("total",       total);
                        resp.put("operation",   Operation.ACCEPT);
                        resp.put("reqOper",     Operation.SELL);
                    }
                    else {
                        resp.put("operation",   Operation.REJECT);
                        resp.put("reason",      "Limit '" + limit
                                                + "' is too high");
                    }
                }
                else {
                    resp.put("operation",   Operation.REJECT);
                    resp.put("reason",      "Symbol '" + symbol
                                            + "' isn't avaliable");
                }
            }
        }
        catch (Exception e) {
            resp.put("operation",   Operation.ERROR);
            resp.put("info",        e.getMessage());
        }
        
        return resp;
    }

    private Message procBuy(Message msg) {
        Message resp    = new Message();
        
        String clientId = msg.asString("clientId");
        String symbol   = msg.asString("symbol");
        double value    = msg.asDouble("value");
        double limit    = msg.asDouble("limit");
        
        resp.put("clientId", clientId);
        resp.put("symbol",   symbol);
        
        try {
            msg.checkBuy();
            
            Book book = Book.instance();
            synchronized (book) {
                if (Book.isAvaliable(symbol)) {
                    
                    Share share = book.get(symbol);
                    
                    double unitValue = share.getUnitValue();
                    double maxQuotas = share.getMaxQuotas();
                    double maxVolume = unitValue * maxQuotas;
                    
                    if (unitValue <= limit) {
                        maxVolume = maxVolume >= value ? value : maxVolume;
                        
                        double quotas   = maxVolume / unitValue;
                        double total    = quotas * unitValue;
                        
                        share.decMaxQuotas(quotas);
                        
                        resp.put("quotas",      quotas);
                        resp.put("value",       unitValue);
                        resp.put("total",       total);
                        resp.put("operation",   Operation.ACCEPT);
                        resp.put("reqOper",     Operation.BUY);
                    }
                    else {
                        resp.put("operation",   Operation.REJECT);
                        resp.put("reason",      "Limit '" + limit
                                                + "' is too low");
                    }
                }
                else {
                    resp.put("operation",   Operation.REJECT);
                    resp.put("reason",      "Symbol '" + symbol
                                            + "' isn't avaliable");
                }
            }
        }
        catch (Exception e) {
            resp.put("operation",   Operation.ERROR);
            resp.put("info",        e.getMessage());
        }
        
        return resp;
    }
}
