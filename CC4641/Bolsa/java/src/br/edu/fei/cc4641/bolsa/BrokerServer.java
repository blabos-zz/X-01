package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.HashMap;

/**
 * Implementa a thread servidora do broker. Cria o socket servidor pelo qual
 * os clientes se conectam. Aceita várias conexões simultâneas. Dispara uma
 * thread para tratar cada nova conexão.
 * 
 * Toda vez que os clientes enviam uma mensagem ao broker, sua thread coloca
 * a mensagem na fila de envio do worker. Toda vez que há uma mensagem na
 * fila local da thread, essa mensagem (que é uma resposta) é enviada ao
 * cliente.
 * 
 * O worker é a thread responsável por pegar as mensagens recebidas pelo
 * broker, enviar ao mercado e repassar a resposta para a thread cliente
 * adequada.
 */
public class BrokerServer extends MarketThread {
    private ServerSocket serverSocket                       = null;
    private static HashMap<String, BrokerClient> clients    = null;
    private Config conf                                     = null;
    
    
    public BrokerServer(Config cfg) {
        super("BrokerServer Thread");
        this.conf   = cfg;
        clients     = new HashMap<String, BrokerClient>();
    }
    
    public void run() {
        try {
            serverSocket = new ServerSocket(conf.getListenPort());
        }
        catch (IOException e) {
            stderr.println(e.getMessage());
            return;
        }
        
        while(!canStop()) {
            try {
                String name = "Client #" + BrokerConsole.nextClientId();
                BrokerClient client
                    = new BrokerClient(name, serverSocket.accept(), conf);
                clients.put(name, client);
                client.start();
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
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
    
    public synchronized void stopMe() {
        super.stopMe();
    }

    protected void cleanup() {
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
            
            if (clients.size() > 0) {
                for (String key : clients.keySet()) {
                    BrokerClient c = clients.get(key);
                    if (c != null) {
                        c.stopMe();
                    }
                }
                clients.clear();
            }
            
                
        }
        catch (Exception e) {
            stderr.println("Error stopping Broker Server");
        }
    }
    
    public static void cleanClient(String name) {
        synchronized (clients) {
            clients.remove(name);
        }
    }

    public BrokerClient getClient(String clientId) {
        return clients.get(clientId);
    }
}



