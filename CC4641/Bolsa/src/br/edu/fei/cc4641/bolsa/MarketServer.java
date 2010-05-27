package br.edu.fei.cc4641.bolsa;
import java.net.*;
import java.util.HashMap;
import java.io.*;

public class MarketServer extends MarketThread {
    private ServerSocket serverSocket               = null;
    static HashMap<String, MarketClient> clients    = null;
    private Config conf                             = null;
    private static int marketClientId               = 0;
    
    
    public MarketServer(Config cfg) {
        this.conf = cfg;      
        MarketServer.clients = new HashMap<String, MarketClient>();
    }

    public void stopMe() {
        super.stopMe();
        cleanup();
    }

    public void run() {
        try {
            serverSocket = new ServerSocket(conf.getListenPort());
        }
        catch (IOException e) {
            stderr.println(e.getMessage());
            return;
        }

        while(!canStop()) {
            try {
                String name = "Market Client #" + nextclientId();
                MarketClient client
                    = new MarketClient(name, serverSocket.accept(), conf);
                clients.put(name, client);
                client.start();
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
        
        cleanup();
    }

    void cleanup() {
        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }
            
            if (clients.size() > 0) {
                for (String key : clients.keySet()) {
                    MarketClient c = clients.get(key);
                    if (c != null) {
                        c.stopMe();
                    }
                }
                clients.clear();
            }
            
                
        }
        catch (Exception e) {
            stderr.println("Error stopping Market Server");
        }
    }

    private static int  nextclientId() {
        return ++MarketServer.marketClientId;
    }

    public static void cleanClient(String name) {
        synchronized (clients) {
            clients.remove(name);
        }
    }
}
