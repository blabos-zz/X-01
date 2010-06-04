package br.edu.fei.cc4641.bolsa;
import java.net.*;
import java.util.HashMap;
import java.io.*;

/**
 * Implementa o servidor da bolsa.
 * 
 * Suporta mais de um cliente simultaneamente. A cada nova conexão, uma nova
 * thread é disparada para tratar a requisição do cliente.
 * 
 * Mantém uma lista de todos os clientes conectados e elimina-os dessa lista a
 * medida que vão se desconectando e suas threads encerram.
 */
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
        if (clients.size() > 0) {
            for (String key : clients.keySet()) {
                MarketClient c = clients.get(key);
                if (c != null) {
                    synchronized(clients) {
                        c.stopMe();
                    }
                }
            }
        }
        super.stopMe();
    }

    public void run() {
        stdout.println("Thread '" + getName() + "' starting");
        
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
        
        stdout.println("Thread '" + getName() + "' ending");
    }

    protected void cleanup() {
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
            
            if (clients.size() > 0) {
                
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
        System.out.println("MarketServer.cleanClient()");
        synchronized (clients) {
            clients.remove(name);
        }
    }
}
