package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.LinkedList;

public class BrokerWorker extends MarketThread {
    public static final int MAX_RETRIES         = 3;
    private Config conf                         = null;
    private NetStream netStream                 = null;
    private LinkedList<Message> messageQueue    = null;
    
    
    public BrokerWorker(String name, Socket client, Config cfg)
    throws IOException {
        super(name);
        conf = cfg;
        netStream = new NetStream(client, cfg);
        messageQueue = new LinkedList<Message>();
    }
    
    public void stopMe() {
        super.stopMe();
        cleanup();
    }
    
    void cleanup() {
        netStream.cleanup();
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
            
            if (msg != null) {
                res = toMarket(msg);
                if (res != null) {
                    BrokerConsole.enqueueToClient(conf.getProtocol(), res);
                }
                else {
                    stopMe();
                }
            }
            else {
                stopMe();
            }
        }
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
    
    private Message toMarket(Message msg) {
        netStream.writeMessage(msg);
        return netStream.readMessage();
    }
}
