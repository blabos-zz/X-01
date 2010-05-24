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
    private BrokerServer server                 = null;
    private LinkedList<Message> messageQueue    = null;
    
    
    public BrokerClient(Socket client, BrokerServer server)
    throws IOException {
        this.clientSocket   = client;
        this.server         = server;
        
        setName("" + BrokerServer.nextClientId());
    
        messageQueue = new LinkedList<Message>();
        
        netOut = new PrintWriter(this.clientSocket.getOutputStream(), true);
        netIn  = new BufferedReader(
                new InputStreamReader(
                        this.clientSocket.getInputStream()));
        
        start();
    }

    private synchronized Message dequeue() {
        stdout.println("BrokerClient.dequeue");
        
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
        messageQueue.addLast(msg);
    }
    
    private Message receiveMessage() {
        stdout.println("BrokerClient.receiveMessage");
        
        Message msg = null;
        
        try {
            String line = netIn.readLine();
            if (line == null) {
                throw new IOException("Connection closed by peer");
            }
            
            msg = new Message(line);
            msg.put("clientId", getName());
            msg.checkHeader();
        }
        catch (IOException e) {
            stdout.println(e.getMessage() + ". Closing client connection");
        }
        catch (Exception e) {
            stdout.println(e.getMessage());
            msg = new Message();
            msg.put("operation", Operation.ERROR);
            msg.put("error", e.getMessage());
            netOut.println(msg.toStr());
            msg = null;
        }
    
        return msg;
    }

    public void run() {
        stdout.println("BrokerClient.run");
        
        while(!canStop()) {
            Message msg = receiveMessage();
            
            if (msg != null) {
                server.enqueueToWorker(msg);
            }
            else {
                return;
            }
    
            synchronized(this) {
                try {
                    stdout.println("BrokerClient.run going sleep");
                    wait();
                }
                catch (Exception e) {
                    e.printStackTrace();
                }
            }
            
            Message res = dequeue();
            
            if (res != null) {
                sendMessage(res);
            }
        }
    }
    
    public void sendMessage(Message msg) {
        netOut.println(msg.toStr());
    }
}
