package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;
import sun.misc.Queue;

public class BrokerServer extends Thread {
	private ServerSocket server	= null;
	
	private boolean stop 		= false;
	
	private Queue queue			= null;
	
	
	public BrokerServer(int port) {
		queue = new Queue();
		start(port);
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
				@SuppressWarnings("unused")
				BrokerClient client = new BrokerClient(this, server.accept());
				System.out.println("Processing new client");
			} catch (IOException e) {
				System.err.println(e.getMessage());
			}
		}
	}

	public synchronized void enqueue(Message msg) {
		queue.enqueue(msg);
	}
}

class BrokerClient extends Thread {
	private BrokerServer server	= null;
	private Socket client		= null;
	private PrintWriter out 	= null;
	private BufferedReader in	= null;
	
	private boolean stop 		= false;
	
	private Queue queue			= null;
	
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
	
	public BrokerClient(BrokerServer server, Socket client) {
		this.server = server;
		this.client = client;
		
		queue = new Queue();
		
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
			
			if (msg != null) {
				server.enqueue(msg);
			}
			else {
				return;
			}
			
			try { wait(); }
			catch (Exception e) {}
			
			Message res = dequeue();
			if (res != null) {
				toClient(msg);
			}
		}
	}

	private void toClient(Message msg) {
		out.println(msg.toStr());
	}

	private synchronized Message dequeue() {
		Message msg = null;
		
		try {
			msg = (Message)queue.dequeue();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		
		return msg;
	}

	private Message readMessage() {
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
