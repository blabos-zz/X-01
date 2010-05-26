package br.edu.fei.cc4641.bolsa;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.LinkedList;

public class BrokerClient extends MarketThread {
    private Socket clientSocket                 = null;
    private BufferedReader netIn                = null;
    private PrintWriter netOut                  = null;
    private BrokerServer brokerServer           = null;
    private LinkedList<Message> messageQueue    = null;
    
    
    public BrokerClient(Socket client, BrokerServer server)
    throws IOException {
        this.clientSocket   = client;
        this.brokerServer         = server;
        
        setName("" + BrokerServer.nextClientId());
    
        messageQueue = new LinkedList<Message>();
        
        netOut = new PrintWriter(this.clientSocket.getOutputStream(), true);
        netIn  = new BufferedReader(
                new InputStreamReader(
                        this.clientSocket.getInputStream()));
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
    
    private Message receiveMessage() {
        Message msg = null;
        
        try {
            msg = new Message(netIn.readLine());
            msg.put("clientId", getName());
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    
        return msg;
    }
    
    public void stopMe() {
        super.stopMe();
        cleanup();
    }

    private void cleanup() {
        if (clientSocket != null && clientSocket.isConnected()) {
            try {
                clientSocket.close();
            } catch (Exception e) {
                stderr.println(e.getMessage());
            }
        }
    }

    public void run() {
        while(!canStop()) {
            Message msg = receiveMessage();
            
            if (msg != null) {
                brokerServer.enqueueToWorker(msg);
                
                synchronized(this) {
                    try {
                        wait();
                    }
                    catch (Exception e) {
                        stderr.println(e.getMessage());
                    }
                }
                
                Message res = dequeue();
                
                if (res != null) {
                    sendMessage(res);
                }
            }
            else {
                stopMe();
            }
        }
    }
    
    public void sendMessage(Message msg) {
        netOut.println(msg.toStr());
    }
}
