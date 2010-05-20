package br.edu.fei.cc4641.bolsa;
import java.net.*;
import java.io.*;

public class MarketServer extends Thread {
	private int port			= 7070;
	private ServerSocket server = null;
	
	private boolean stop 		= false;
	
	private Console console		= null;
	
	public MarketServer(int port) {
		this.port		= ((port > 1023) && (port < 65536)) ? port: 7070;
		this.console	= new Console(this);
		start();
	}
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public void stopMe() {
		synchronized (this) {
			stop = true;
		}
		
		try {
			server.close();
			sleep(100);
		}
		catch (Exception e) {}
		
		if (isAlive()) interrupt();
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

class MarketClient extends Thread {
	private Socket client		= null;
	private PrintWriter out 	= null;
	private BufferedReader in	= null;
	
	private boolean stop = false;
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public void stopMe() {
		synchronized (this) {
			stop = true;
		}
		
		try {
			sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		if (isAlive()) interrupt();
	}
	
	public MarketClient(Socket client) {
		this.client = client;
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
		
		while (!canStop()) {
			Message msg = null;
			Message res = null;
			
			msg = getMsg();
			
			if (msg == null) {
				out.close();
				return;
			}
			
			System.out.println(msg.toXML());
			
			switch (msg.asInt("operation")) {
				case Operation.BUY:
					res = procBuy(msg);
					break;
				case Operation.SELL:
					res = procSell(msg);
					break;
				case Operation.INFO_REQUEST:
					res = procInfo(msg);
					break;
				case Operation.GREETING:
					res = procGreeting(msg);
					break;
				default:
					res = procOperNotFound(msg);
			}
			
			System.out.println(res.toXML());
			out.println(res.toStr());
		}
	}

	private Message getMsg() {
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

	private Message procGreeting(Message msg) {
		Message resp = new Message();
		
		try {
			String greeting = "";
			
			msg.ckeckGreeting();
			
			System.out.println(msg.toXML());
			
			greeting += "Welcome " + msg.asString("clientId") + "! ";
			greeting += "I'm Market v 2.0. ";
			greeting += "Messages Supported: ";
			for (String name : Operation.names) {
				greeting += name + ", ";
			}
			greeting = greeting.substring(0, greeting.length() - 2) + ".";
			
			resp.put("clientId", msg.get("clientId"));
			resp.put("operation", Operation.GREETING);
			resp.put("greet", greeting);
		}
		catch (InvalidMessage e) {
			System.err.println(e.getMessage());
			
			resp.put("clientId", msg.get("clientId"));
			resp.put("operation", Operation.ERROR);
			resp.put("info", e.getMessage());
		}
		
		return resp;
	}

	private Message procInfo(Message msg) {
		Message resp = new Message();
		
		resp.put("clientId", msg.asString("clientId"));
		
		try {
			msg.ckeckInfoRequest();
			
			resp.put("clientId", msg.get("clientId"));
			resp.put("operation", Operation.INFO_RESPONSE);
			resp.put("info", Book.getMarketInfo());
		}
		catch (InvalidMessage e) {
			resp.put("clientId", msg.get("clientId"));
			resp.put("operation", Operation.ERROR);
			resp.put("info", e.getMessage());
		}
		
		return resp;
	}

	private Message procOperNotFound(Message msg) {
		Message resp = new Message();
		resp.put("clientId", msg.asString("clientId"));
		resp.put("operation", Operation.ERROR);
		resp.put("error", "Operation '" + msg.asInt("operation")
				+ "' was not supported");
		
		return resp;
	}

	private Message procSell(Message msg) {
		Message resp = new Message();
		
		resp.put("clientId", msg.asString("clientId"));
		
		try {
			msg.checkSell();
			
			String symbol	= msg.asString("symbol");
			double quota	= msg.asDouble("quota");
			double limit	= msg.asDouble("limit");
			
			Book book = Book.instance();
			synchronized (book) {
				if (book.containsKey(symbol)) {
					resp.put("operation", Operation.ACCEPT);
					
					Share share = book.get(symbol);
					
					double unitValue = share.getUnitValue();
					
					if (unitValue >= limit) {
						double total = quota * unitValue;
						share.incMaxQuotas(quota);
						resp.put("value", unitValue);
						resp.put("total", total);
					}
					else {
						resp.put("value", 0);
						resp.put("total", 0);
					}

                                        resp.put("reqOper", Operation.SELL);
				}
				else {
					resp.put("operation", Operation.ERROR);
					resp.put("error", "Symbol '" + symbol
							+ "' isn't avaliable");
				}
			}
		}
		catch (Exception e) {
			resp.put("operation", Operation.ERROR);
			resp.put("info", e.getMessage());
		}
		
		return resp;
	}

	private Message procBuy(Message msg) {
		Message resp = new Message();
		
		resp.put("clientId", msg.asString("clientId"));
		
		try {
			msg.checkBuy();
			
			String symbol	= msg.asString("symbol");
			double value	= msg.asDouble("value");
			double limit	= msg.asDouble("limit");
			
			Book book = Book.instance();
			synchronized (book) {
				if (Book.isAvaliable(symbol)) {
					resp.put("operation", Operation.ACCEPT);
					
					Share share = book.get(symbol);
					
					double unitValue = share.getUnitValue();
					double maxQuotas = share.getMaxQuotas();
					double maxVolume = unitValue * maxQuotas;
					
					if (unitValue <= limit) {
						maxVolume = maxVolume >= value ? value : maxVolume;
						double quota = maxVolume / unitValue;
						share.decMaxQuotas(quota);
						resp.put("quota", quota);
						resp.put("total", maxVolume);
					}
					else {
						resp.put("quota", 0);
						resp.put("total", 0);
					}

                                        resp.put("reqOper", Operation.BUY);
				}
				else {
					resp.put("operation", Operation.ERROR);
					resp.put("error", "Symbol '" + symbol + "' isn't avaliable");
				}
			}
		}
		catch (Exception e) {
			resp.put("operation", Operation.ERROR);
			resp.put("info", e.getMessage());
		}
		
		return resp;
	}
}


class Console extends Thread {
	private MarketServer server			= null;
	private boolean stop			= false;
	
	private BufferedReader stdin	= null;
    private PrintStream stdout		= null;
    private PrintStream stderr		= null;
	
	public Console(MarketServer server) {
		this.server = server;
	}
	
	@Override
	protected void finalize() throws Throwable {
		stopMe();
		super.finalize();
	}
	
	public synchronized boolean canStop() {
		return stop;
	}
	
	public void stopMe() {
		synchronized (this) {
			stop = true;
		}
	}
	
	public void run() {
		stdin	= new BufferedReader(new InputStreamReader(System.in));
		stdout	= System.out;
		stderr	= System.err;
		
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