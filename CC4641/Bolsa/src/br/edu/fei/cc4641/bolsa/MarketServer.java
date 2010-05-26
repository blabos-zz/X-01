package br.edu.fei.cc4641.bolsa;
import java.net.*;
import java.util.HashMap;
import java.io.*;

public class MarketServer extends MarketThread {
    private int port                    = 7070;
    private ServerSocket serverSocket   = null;
    private MarketServerConsole console = null;
    
    static HashMap<String, MarketClient> clients = null;
    private static int marketClientId = 0;

    public MarketServer(int port) {
        this.port       = ((port > 1023) && (port < 65536)) ? port: 7070;
        this.console    = new MarketServerConsole(this);
        
        MarketServer.clients = new HashMap<String, MarketClient>();
    }

    public void stopMe() {
        super.stopMe();
        cleanup();
    }

    public void run() {
        try {
            serverSocket = new ServerSocket(port);
        }
        catch (IOException e) {
            stderr.println(e.getMessage());
            return;
        }
        
        console.start();

        while(!canStop()) {
            try {
                String name = "Market Client #" + nextclientId();
                MarketClient client
                    = new MarketClient(name, serverSocket.accept());
                clients.put(name, client);
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
        
        cleanup();
    }

    private void cleanup() {
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
            MarketClient c = clients.get(name);
            if (c != null) {
                c = null;
            }
            clients.remove(name);
        }
    }
}
