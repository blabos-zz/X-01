package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.HashMap;


public class BrokerServer extends MarketThread {
    private int brokerServerPort                    = 7080;
    private String marketHost                       = "localhost";
    private int marketPort                          = 7070;
    
    private ServerSocket brokerServerSocket         = null;
    private BrokerMarketWorker marketWorker         = null;
    HashMap<String, BrokerClient> clients           = null;
    
    private static int clientId                     = 0;
    
    private BrokerConsole console                   = null;
    
    
    public BrokerServer(int brokerPort, String marketHost, int marketPort)
    throws IOException {
        this.brokerServerPort   = brokerPort;
        this.marketHost         = marketHost;
        this.marketPort         = marketPort;
        
        brokerServerSocket      = new ServerSocket(brokerServerPort);
        clients                 = new HashMap<String, BrokerClient>();
        

        marketWorker            = new BrokerMarketWorker(this);
        console                 = new BrokerConsole(this);
    }
    
    public void enqueueToClient(Message msg) {
        String clientId = msg.asString("clientId");
        BrokerClient client = clients.get(clientId);
        
        if (client != null) {
            client.enqueue(msg);
            
            try {
                synchronized (client) {
                    client.notify();
                }
            }
            catch (Exception e) {
                stderr.println(e.getMessage());
            }
        }
    }
    
    public void enqueueToWorker(Message msg) {
        marketWorker.enqueue(msg);
        
        try {
            synchronized (marketWorker) {
                marketWorker.notify();
            }
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    }
    
    public String marketHost() {
        return marketHost;
    }

    public int marketPort() {
        return marketPort;
    }

    public void run() {

        console.start();
        marketWorker.start();
        
        while(!canStop()) {
            try {
                synchronized (clients) {
                    BrokerClient client
                        = new BrokerClient(brokerServerSocket.accept(), this);
                    clients.put(client.getName(), client);
                    client.start();
                }   
            }
            catch (Exception e) {
                stderr.println(e.getMessage());
            }
        }
        
        marketWorker.stopMe();
        console.stopMe();
    }
    
    public synchronized void stopMe() {
        super.stopMe();
        cleanup();
    }

    private void cleanup() {
        try {
            for (String key : clients.keySet()) {
                BrokerClient c = clients.get(key);
                c.stopMe();
            }
            clients.clear();
            
            if (brokerServerSocket != null && !brokerServerSocket.isClosed()){
                brokerServerSocket.close();
            }
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    }

    public synchronized static int nextClientId() {
        return ++BrokerServer.clientId;
    }
}



