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
        this.brokerServer = server;
        this.messageQueue = new LinkedList<Message>();
    }
    
    private synchronized Message dequeue() {
        Message msg = null;
        
        try {
            msg = messageQueue.removeFirst();
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
        
        return msg;
    }
    
    public synchronized void enqueue(Message msg) {
        messageQueue.addLast(msg);
    }
    
    private boolean connectionOk() {
        int retries = 0;
        
        if (marketSocket != null && marketSocket.isConnected()) {
            return true;
        }
        
        while (retries < MAX_RETRIES) {
            try {
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
                stderr.println(e.getMessage());
                retries++;
            }
        }
        
        return false;
    }

    public void run() {
        Message msg = null;
        Message res = null;
        
        while (!canStop()) {
            if (messageQueue.size() <= 0) {
                synchronized(this) {
                    try {
                        wait();
                    }
                    catch (Exception e) {
                        stderr.println(e.getMessage());
                    }
                }
            }
            
            msg = dequeue();
            
            if (msg != null && connectionOk()) {
                res = toMarket(msg);
                if (res != null) {
                    brokerServer.enqueueToClient(res);
                }
                else {
                    marketSocket = null;
                }
            }
            else {
                stopMe();
            }
        }
    }
    
    public synchronized void stopMe() {
        super.stopMe();
        cleanup();
    }
    
    private void cleanup() {
        try {
            if (marketSocket != null && marketSocket.isConnected()) {
                marketSocket.close();
            }
        }
        catch (Exception e){
            stderr.println(e.getMessage());
        }
    }

    private Message toMarket(Message msg) {
        sendMessage(msg);
        return receiveMessage();
    }

    private Message receiveMessage() {
        Message msg = null;
        
        try {
            msg = new Message(netIn.readLine());
        } catch (Exception e) {
            stderr.println(e.getMessage());
        }
        
        return msg;
    }
    
    private void sendMessage(Message msg) {
        netOut.println(msg.toStr());
    }
}
