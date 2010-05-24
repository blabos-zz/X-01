package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.LinkedList;

public class BrokerMarketWorker extends MarketThread {
    public static final int MAX_RETRIES         = 3;
    private BrokerServer brokerServer           = null;
    private static Socket marketSocket          = null;
    private static BufferedReader netIn         = null;
    private static PrintWriter netOut           = null;
    private LinkedList<Message> messageQueue    = null;
    
    public BrokerMarketWorker(BrokerServer server) {
        stderr.println("BrokerMarketWorker.BrokerMarketWorker");
        
        this.brokerServer = server;
        this.messageQueue = new LinkedList<Message>();
        
        start();
    }
    
    private synchronized Message dequeue() {
        stderr.println("BrokerMarketWorker.dequeue");
        
        Message msg = null;
        
        try {
            msg = (Message)messageQueue.removeFirst();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        
        return msg;
    }
    
    public synchronized void enqueue(Message msg) {
        stderr.println("BrokerMarketWorker.enqueue: "
                + msg.toStr());
        
        messageQueue.addLast(msg);
        stderr.println("BrokerMarketWorker.enqueue.end");
    }
    
    private boolean reconnect() {
        stderr.println("BrokerMarketWorker.reconnect");
        
        int retries = 0;
        
        if (marketSocket != null && marketSocket.isConnected()) {
            return true;
        }
        
        while (retries < MAX_RETRIES) {
            try {
                marketSocket    = null;
                netOut          = null;
                netIn           = null;

                marketSocket
                    = new Socket(brokerServer.marketHost(),
                            brokerServer.marketPort());
                
                netOut
                    = new PrintWriter(marketSocket.getOutputStream(), true);
                
                netIn
                    = new BufferedReader(new InputStreamReader(
                            marketSocket.getInputStream()));
                
                return true;
            }
            catch (Exception e) {
                e.printStackTrace();
                retries++;
            }
        }
        
        return false;
    }

    public void run() {
        stderr.println("BrokerMarketWorker.run");
        
        Message msg = null;
        Message res = null;
        
        while (!canStop()) {
            if (messageQueue.size() <= 0) {
                synchronized(this) {
                    try {
                        stdout.println("BrokerMarketWorker.run going sleep");
                        wait();
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
            
            if (reconnect()) {
                msg = dequeue();
                
                if (msg != null) {
                    res = toMarket(msg);
                }
                
                if (res != null) {
                    brokerServer.enqueueToClient(res);
                }
            }
            else {
                stopMe();
            }
        }
    }
    
    public synchronized void stopMe() {
        stderr.println("BrokerMarketWorker.stopMe");
        
        try {
            marketSocket.close();
        }
        catch (Exception e){
            e.printStackTrace();
        }
        
        super.stopMe();
    }
    
    private Message toMarket(Message msg) {
        stderr.println("BrokerMarketWorker.toMarket");
        
        sendMessage(msg);
        return receiveMessage();
    }

    private Message receiveMessage() {
        stderr.println("BrokerMarketWorker.receiveMessage");
        
        Message msg = null;
        
        try {
            msg = new Message(netIn.readLine());
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return msg;
    }
    
    private void sendMessage(Message msg) {
        stderr.println("BrokerMarketWorker.sendMessage");
        
        netOut.println(msg.toStr());
    }
}
