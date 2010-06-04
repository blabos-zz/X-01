package br.edu.fei.cc4641.bolsa;

import java.io.IOException;
import java.util.HashMap;

/**
 * Implementa o console que é utilizado para passar comandos para o servidor
 * como um singleton.
 */
public class MarketServerConsole extends MarketThread {
    private static MarketServerConsole myself       = null;
    private HashMap<String, MarketServer> servers   = null;
    
    protected MarketServerConsole() {
        super("MarketServerConsole Thread");
        servers = new HashMap<String, MarketServer>();
    }
    
    public synchronized static MarketServerConsole instance() {
        if (myself == null) {
            myself = new MarketServerConsole();
            myself.start();
        }
        
        return myself;
    }
    
    public void newMarketServer(String name, int port, int proto) {
        MarketServer server
            = new MarketServer(new Config("", 0, port, proto));
        
        server.start();
        
        servers.put("" + proto, server);
    }
    
    public void stopMe() {
        super.stopMe();
    }

    protected void cleanup() {
        for (MarketServer server: servers.values()) {
            server.stopMe();
        }
        servers.clear();
    }
    
    public void run() {
        stdout.println("Thread '" + getName() + "' starting");
        
        stdout.println("Market Console");
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
        stdout.println("Market Server Help");
        stdout.println("Commands:");
        stdout.println("    help     - Displays this message.");
        stdout.println("    exit     - Exits and stops the server.");
    }

    void prompt() {
        stdout.print("# ");
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
}
