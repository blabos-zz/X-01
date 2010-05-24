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
    private HashMap<String, BrokerClient> clients   = null;
    
    private static int clientId                     = 0;
    
    
    public BrokerServer(int brokerPort, String marketHost, int marketPort)
    throws IOException {
        stderr.println("BrokerServer.BrokerServer");
        
        this.brokerServerPort   = brokerPort;
        this.marketHost         = marketHost;
        this.marketPort         = marketPort;
        
        brokerServerSocket      = new ServerSocket(brokerServerPort);
        marketWorker            = new BrokerMarketWorker(this);
        clients                 = new HashMap<String, BrokerClient>();
        
        start();
    }
    
    public void enqueueToClient(Message msg) {
        stderr.println("BrokerServer.enqueueToClient");
        
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
                e.printStackTrace();
            }
        }
    }
    
    public void enqueueToWorker(Message msg) {
        stderr.println("BrokerServer.enqueueToWorker");
        
        marketWorker.enqueue(msg);
        
        try {
            synchronized (marketWorker) {
                marketWorker.notify();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        
    }
    
    public String marketHost() {
        stderr.println("BrokerServer.sendMessage");
        
        return marketHost;
    }

    public int marketPort() {
        stderr.println("BrokerServer.marketPort");
        
        return marketPort;
    }

    public void run() {
        stderr.println("BrokerServer.run");
        
        while(!canStop()) {
            try {
                BrokerClient client
                    = new BrokerClient(brokerServerSocket.accept(), this);
                clients.put(client.getName(), client);
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    
    public synchronized void stopMe() {
        stderr.println("BrokerServer.stopMe");
        
        try {
            brokerServerSocket.close();
            marketWorker.stopMe();
            
            super.stopMe();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public synchronized static int nextClientId() {
        System.err.println("BrokerServer.nextClientId");
        
        return ++BrokerServer.clientId;
    }
}



