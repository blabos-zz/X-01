package br.edu.fei.cc4641.bolsa;
import java.net.*;
import java.io.*;

public class MarketServer extends MarketThread {
    private int port                    = 7070;
    private ServerSocket server         = null;
    private MarketServerConsole console = null;

    public MarketServer(int port) {
        this.port       = ((port > 1023) && (port < 65536)) ? port: 7070;
        this.console    = new MarketServerConsole(this);
        start();
    }

    public void stopMe() {
        try {
            server.close();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        super.stopMe();
    }

    public void run() {
        try {
            server = new ServerSocket(port);
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
            return;
        }
        
        console.start();

        while(!canStop()) {
            try {
                @SuppressWarnings("unused")
                MarketClient client = new MarketClient(server.accept());
                System.out.println("Processing new client");
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
    }
}
