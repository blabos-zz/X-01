package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.LinkedList;

/**
 * Trata uma requisição de um cliente, basicamente colocando a mensagem do
 * cliente na fila do worker e pegando as mensagens de resposta em sua fila
 * local e enviando ao cliente.
 */
public class BrokerClient extends MarketThread {
    private Config conf                         = null;
    private NetStream netStream                 = null;
    private LinkedList<Message> messageQueue    = null;
    
    
    public BrokerClient(String name, Socket client, Config cfg)
    throws IOException {
        super(name);
        conf = cfg;
        netStream = new NetStream(client, cfg);
        messageQueue = new LinkedList<Message>();
    }
    
    public synchronized void stopMe() {
        super.stopMe();
    }
    
    protected void cleanup() {
        netStream.cleanup();
    }
    
    public void run() {
        while(!canStop()) {
            Message msg = null;
            Message res = null;
            
            msg = netStream.readMessage();
            
            if (msg == null) {
                netStream = null;
                break;
            }
            
            msg.put("clientId", getName());
            
            BrokerConsole.enqueueToWorker(conf.getProtocol(), msg);
            
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
            
            res = dequeue();
            
            if (res != null) {
                netStream.writeMessage(res);
            }
        }
        
        BrokerServer.cleanClient(getName());
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
}
