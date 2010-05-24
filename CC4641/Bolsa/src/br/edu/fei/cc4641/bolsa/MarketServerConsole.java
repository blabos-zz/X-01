package br.edu.fei.cc4641.bolsa;

import java.io.IOException;

public class MarketServerConsole extends MarketThread {
    private MarketServer server = null;
    
    public MarketServerConsole(MarketServer server) {
        this.server = server;
    }
    
    @Override
    protected void finalize() throws Throwable {
        stopMe();
        super.finalize();
    }
    
    public void run() {
        System.out.println("Market Console");
        while(!canStop()) {
            try {
                prompt();
                execute(nextCmd());
            } catch (IOException e) {
                System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
        
        stopSever();
    }

    private void execute(String cmd) {
        if (cmd == null || cmd.equals("exit")) {
            exitMe();
        }
        else if (cmd.equals("help")) {
            printHelp();
        }
        else {
            error(cmd);
        }
    }

    private void exitMe() {
        stopMe();
    }

    private void error(String cmd) {
        if (cmd.length() > 0) {
            stderr.println("Invalid command '" + cmd + "'");
        }
    }

    private void stopSever() {
        if (server.isAlive()) {
            server.stopMe();
        }
    }

    private void printHelp() {
        stdout.println("Market Server Help");
        stdout.println("Commands:");
        stdout.println("    help - Displays this message.");
        stdout.println("    exit - Exits and stops the server.");
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
