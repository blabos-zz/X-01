package br.edu.fei.cc4641.bolsa;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;

public class MarketThread extends Thread {
    private boolean stop            = false;
    
    protected BufferedReader stdin  = null;
    protected PrintStream stdout    = null;
    protected PrintStream stderr    = null;
    
    public MarketThread() {
        super();
        _init();
    }
    
    public MarketThread(String name) {
        super(name);
        _init();
    }
    
    public synchronized boolean canStop() {
        return stop;
    }
    
    public void stopMe() {
        synchronized (this) {
            stop = true;
        }
        
        try {
            sleep(100);
            if (isAlive()) interrupt();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
    
    private void _init() {
        stdin   = new BufferedReader(new InputStreamReader(System.in));
        stdout  = System.out;
        stderr  = System.err;
    }
}
