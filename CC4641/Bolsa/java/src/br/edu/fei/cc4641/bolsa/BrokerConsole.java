package br.edu.fei.cc4641.bolsa;

import java.io.IOException;
import java.net.Socket;
import java.util.HashMap;

/**
 * Implementa o console de comandos do broker como um singleton.
 */
public class BrokerConsole extends MarketThread {
    private static BrokerConsole myself             = null;
    private HashMap<String, BrokerServer> servers   = null;
    private HashMap<String, BrokerWorker> workers   = null;
    private static int brokerClientId               = 0;
    
    public BrokerConsole() {
        servers = new HashMap<String, BrokerServer>();
        workers = new HashMap<String, BrokerWorker>();
    }
    
    public synchronized static BrokerConsole instance() {
        if (myself == null) {
            myself = new BrokerConsole();
            myself.start();
        }
        
        return myself;
    }
    
    public void newBrokerInstance(String name, String marketHost,
            int marketPort, int listenPort, int proto) {
        
        try {
            Config conf = new Config(marketHost, marketPort, listenPort, proto);
            Socket work = new Socket(marketHost, marketPort);
            
            BrokerServer server = new BrokerServer(conf);
            BrokerWorker worker = new BrokerWorker(name, work, conf);
            
            servers.put("" + proto, server);
            workers.put("" + proto, worker);
            
            server.start();
            worker.start();
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    }
    
    public void stopMe() {
        super.stopMe();
    }
    
    protected void cleanup() {
        for (BrokerServer server: servers.values()) {
            server.stopMe();
        }
        servers.clear();
        
        for (BrokerWorker worker: workers.values()) {
            worker.stopMe();
        }
        workers.clear();
    }
    
    public void run() {
        stdout.println("Thread '" + getName() + "' starting");
        
        stdout.println("Broker Console");
        while(!canStop()) {
            try {
                prompt();
                execute(nextCmd());
            } catch (IOException e) {
                System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
        
        stdout.println("Thread '" + getName() + "' ending");
    }
    
    private void prompt() {
        stdout.print("% ");
    }
    
    private String nextCmd() throws IOException {
        String line = null;
        try {
            line = stdin.readLine().toLowerCase();
        }
        catch (Exception e) {}
        
        if (line == null) stdout.print("EOF");
        
        return line; 
    }
    
    private void execute(String cmd) {
        if (cmd == null || cmd.equals("exit")) {
            stopMe();
        }
        else if (cmd.equals("help")) {
            printHelp();
        }
        else {
            error(cmd);
        }
    }
    
    private void error(String cmd) {
        if (cmd.length() > 0) {
            stderr.println("Invalid command '" + cmd + "'");
        }
    }
    
    private void printHelp() {
        stdout.println("Broker Help");
        stdout.println("Commands:");
        stdout.println("    help     - Displays this message.");
        stdout.println("    exit     - Exits and stops the server.");
    }

    public synchronized static void enqueueToWorker(int proto, Message msg) {
        String key = "" + proto;
        BrokerWorker worker = instance().workers.get(key);
        
        synchronized (worker) {
            worker.enqueue(msg);
            worker.notify();
        }
    }
    
    public synchronized static void enqueueToClient(int proto, Message msg) {
        String key = "" + proto;
        BrokerServer server = instance().servers.get(key);
        
        String clientId = msg.asString("clientId");
        BrokerClient client = server.getClient(clientId);
        
        synchronized (client) {
            client.enqueue(msg);
            client.notify();
        }
    }
    
    static int  nextClientId() {
        return ++BrokerConsole.brokerClientId;
    }
}
