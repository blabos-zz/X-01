package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import java.util.LinkedList;
import java.util.HashMap;


public class BrokerServer extends Thread {
	private ServerSocket server	                        = null;
	private boolean stop 		                        = false;
	private static int clientId                         = 0;
	
	private HashMap<String, BrokerClient> clientTable   = null;
	
	
	public BrokerServer(int port) {
		queue       = new LinkedList<Message>();
		clientTable = new HashMap<String, BrokerClient>();
		start(port);
	}
	
	public synchronized int nextClientId() {
	    return ++BrokerServer.clientId;
	}
	
	public synchronized boolean start(int port) {
		boolean ret = false;
		
		try {
			server = new ServerSocket(port);
			ret = true;
			super.start();
		} catch (IOException e) {
			System.err.println("BrokerServer::start: " + e.getMessage());
			ret = false;
		}
		
		return ret;
	}
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public synchronized boolean stopMe() {
		boolean ret = false;
		
		stop = true;
		
		try {
			if (server != null) {
				server.close();
				server = null;
				ret = true;
			}
		} catch (IOException e) {
			System.err.println("BrokerServer::stop: " + e.getMessage());
			ret = false;
		}
		
		try { sleep(100); }
		catch (Exception e) {}
		
		if (isAlive()) interrupt();
		
		return ret;
	}
	
	public void run() {
		while(!canStop()) {
			try {
				BrokerClient client
				    = new BrokerClient(this, server.accept(), worker);
				    
				clientTable[client.getClientId()]
				    = client;
				
				System.out.println("Processing new client");
			} catch (IOException e) {
				System.err.println(e.getMessage());
			}
		}
	}

	public synchronized void enqueue(Message msg) {
	    System.out.println("BrokerServer.enqueue");
		queue.addLast(msg);
	}
}

class BrokerClient extends Thread {
	private BrokerServer server	        = null;
	private MarketWorker worker         = null;
	private Socket client		        = null;
	private PrintWriter out 	        = null;
	private BufferedReader in	        = null;
	
	private boolean stop 		        = false;
	private int clientId                = 0;
	
	private LinkedList<Message> queue	= null;
	
	
	public int getClientId() {
	    return clientId;
	}
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public void stopMe() {
		synchronized (client) {
			stop = true;
		}
		
		try {
			sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		if (isAlive()) interrupt();
	}
	
	public BrokerClient(BrokerServer server, Socket client,
	                    MarketWorker worker) {
		this.server = server;
		this.client = client;
		this.worker = worker;
		
		synchronized (this.server) {
		    this.clientId = this.server.nextClientId();
		}
		
		queue = new LinkedList<Message>();
		
		try {
			out	= new PrintWriter(this.client.getOutputStream(), true);
			in	= new BufferedReader(
					new InputStreamReader(this.client.getInputStream()));
		} catch (IOException e) {
			System.err.println(e.getMessage());
			return;
		}
        
		start();
	}
	
	public void run() {
		while(!canStop()) {
			Message msg = readMessage();
			
			System.out.println("BrokerClient.run");
			
			if (msg != null) {
				worker.enqueue(msg);
				worker.notify();
			}
			else {
				return;
			}
			
			server.printQueue();
			
			synchronized(this) {
			    try {
			        wait();
			    } catch (Exception e) {
			        System.out.println(e.getMessage());
		        }
		    }
			
			Message res = dequeue();
			if (res != null) {
				toBroker(msg);
			}
		}
	}

	private void toBroker(Message msg) {
	System.out.println("BrokerClient.toBroker");
		out.println(msg.toStr());
	}

	private synchronized Message dequeue() {
		Message msg = null;
		
		System.out.println("BrokerClient.dequeue");
		
		try {
			msg = (Message)queue.removeFirst();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		
		return msg;
	}

	private Message readMessage() {
	System.out.println("BrokerClient.readMessage");
		Message msg = null;
		try {
			String line = in.readLine();
			if (line == null) {
				throw new IOException("Connection closed by peer");
			}
			
			msg = new Message(line);
			
			msg.checkHeader();
		} catch (IOException e) {
			System.out.println(e.getMessage()
					+ ". Closing client connection");
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
			msg = new Message();
			msg.put("operation", Operation.ERROR);
			msg.put("error", e.getMessage());
			out.println(msg.toStr());
			msg = null;
		}
		
		return msg;
	}
}


class MarketWorker extends Thread {
    public static final int MAX_RETRIES = 3;
    
    private String host                 = "localhost";
    private int port                    = 7070;
    private int retries                 = 0;
    
    private static Socket client		= null;
    private static PrintWriter out		= null;
    private static BufferedReader in	= null;
    
    private LinkedList<Message> queue   = null;
    
    public MarketWorker(String host, int port) {
        this.host = host;
        this.port = port;
    }
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public synchronized boolean stopMe() {
		boolean ret = false;
		
		stop = true;
		
		try {
			if (server != null) {
				server.close();
				server = null;
				ret = true;
			}
		} catch (IOException e) {
			System.err.println("BrokerServer::stop: " + e.getMessage());
			ret = false;
		}
		
		try { sleep(100); }
		catch (Exception e) {}
		
		if (isAlive()) interrupt();
		
		return ret;
	}
	
	public void printQueue() {
	    System.out.println(queue.size());
	}
    
    public void run() {
        while (!canStop()) {
			if (reconnect()) {
				if ((cmd = command()) == EXIT || cmd == NULL) continue;
				
				msg = collect();
				
				if (msg != null) {
					send(msg);
					msg = receive();
					show(msg);
				}
				else {
					cmd = EXIT;
				}
			}
			
			if (retries >= MAX_RETRIES) {
				stderr.println("Cannot connect to " + host + ":" + port);
				cmd = EXIT;
			}
		}
    }
    
    private static boolean reconnect() {
		if (client != null && client.isConnected()) {
			retries = 0;
			return true;
		}
		
		try {
			client = null;
			out = null;
			in = null;
			
            client = new Socket(host, port);
            out = new PrintWriter(client.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(
            		client.getInputStream()));
            
            retries = 0;
			return true;
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host: " + host + ".");
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for "
                               + "the connection to: " + host + ":" + port
                               + ": " + e.getMessage());
        }
        
        try {
            sleep(1000);
        }
        catch (Exception e) {
            System.err.println(e);
        }
            
        retries++;
		return false;
	}
}
