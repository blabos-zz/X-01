package br.edu.fei.cc4641.bolsa;

import java.io.IOException;

public class BrokerConsole extends MarketThread {
    private BrokerServer server = null;
    
    public BrokerConsole(BrokerServer server) {
        this.server = server;
    }
    
    public void run() {
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
        
        stopBroker();
    }
    
    private void stopBroker() {
        if (server.isAlive()) {
            server.stopMe();
        }
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
        else if (cmd.equals("clients")) {
            printClients();
        }
        else {
            error(cmd);
        }
    }
    
    private void printClients() {
        stdout.println("\nMarket Clients:");
        
        if (server.clients.size() > 0) {
            for (String key : server.clients.keySet()) {
                stdout.println(key);
            }
        }
        else {
            stdout.println("No active clients");
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
        stdout.println("    clients  - Show active clients.");
    }
}
