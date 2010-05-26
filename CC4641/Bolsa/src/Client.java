import java.io.*;
import java.net.*;
import java.util.HashMap;

import br.edu.fei.cc4641.bolsa.*;

public class Client {
    public static void main(String[] args) {
        ClientAgent agent = new ClientAgent("localhost", 7080);
        agent.start();
    }
}


class ClientAgent extends MarketThread {
    private final int CMD_NULL      = -2;
    private final int CMD_INIT      = -1;
    private final int CMD_EXIT      = 0;
    private final int CMD_SEND      = 1;
    private final int CMD_SHOW      = 2;
    
    private String host             = "localhost";
    private int port                = 7080;
    
    private Socket clientSocket     = null;
    private PrintWriter netOut      = null;
    private BufferedReader netIn    = null;
    private String clientId;
    
    
    public ClientAgent(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public void stopMe() {
        cleanup();
        super.stopMe();
    }
    
    public void run() {
        int cmd = CMD_NULL;
        
        if (sendGreeting()) {
            stdout.println("Market Client ver 1.0");
            stdout.println("clientId: " + this.clientId);
        }
        
        while (!canStop()) {
            if (connectionOk() && ((cmd = netxCommand()) != CMD_EXIT)) {
                Message response = null;
                
                switch (cmd) {
                    case CMD_SEND:
                        sendNewOrder();
                        response = receiveResponse();
                        showResponse(response);
                        updateAccount(response);
                        break;
                        
                    case CMD_SHOW:
                        showAccountInfo();
                        break;
                        
                    default:
                        break;
                }
            }
            else {
                stopMe();
            }
        }
    }
    
    private boolean sendGreeting() {
        boolean ret = false;
        
        if (connectionOk()) {
            Message res = null;
            try {
                netOut.println("operation=" + Operation.GREETING
                        + "&greet=Hello+World\n");
                
                res = new Message(netIn.readLine());
                this.clientId = res.asString("clientId");
                ret = true;
            } catch (Exception e) {
                stderr.println(e.getMessage());
                ret = false;
            }
        }
        
        return ret;
    }

    private void showResponse(Message response) {
        if (response != null) {
            stdout.println("\nMarket Response:\n");
            stdout.printf("Raw Data: {\n%s\n}\n\n", response.toStr());
            stdout.println("Visual Data:");
            
            int oper = response.asInt("operation");
            
            if (oper == Operation.INFO_RESPONSE) {
                showInfo(response);
            }
            else if (oper == Operation.GREETING) {
                showGreeting(response);
            }
            else {
                stdout.println(response.toXML());
            }
        }
        else {
            stdout.println("Invalid response received");
        }
    }

    private void showGreeting(Message msg) {
        String greet = msg.asString("greet");
        stdout.println(greet);
    }

    private void showInfo(Message msg) {
        MarketInfo info = new MarketInfo(msg);
        info.print();
    }
    
    private void showAccountInfo() {
        stdout.println();
        stdout.println("Client Account Info:");
        
        Account account = Account.instance();
        stdout.println("+-------------------------+");
        stdout.printf("| Balance:  %13.2f |\n", account.getBalance());
        
        stdout.println("+---------+---------------+");
        stdout.println("|  Symbol |     Quotas    |");
        stdout.println("+---------+---------------+");
        for (Share s : account.values()) {
            stdout.printf("|  %s  | %13.2f |\n", s.getSymbol(), s.getQuotas());
        }
        stdout.println("+---------+---------------+");
    }

    private void updateAccount(Message response) {
        int oper    = response.asInt("operation");
        int reqOper = response.asInt("reqOper");
        
        if (oper == Operation.ACCEPT) {
            String symbol = response.asString("symbol");
            
            double value    = response.asDouble("value");
            double quotas   = response.asDouble("quotas");
            double total    = response.asDouble("total");
            
            Account account = Account.instance();
            if (reqOper == Operation.BUY) {
                account.updateShare(symbol, +quotas);
                account.updBalance(-total);
            }
            else {
                account.updateShare(symbol, -quotas);
                account.updBalance(+total);
            }
        }
    }

    private Message receiveResponse() {
        Message msg = null;
        
        try {
            msg = new Message(netIn.readLine());
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }

        return msg;
    }

    private void sendNewOrder() {
        Message msg = collectFields();
        
        if (msg != null) {
            netOut.println(msg.toStr());
        }
        else {
            stderr.println("Invalid message generated. Not sending");
        }
    }

    private Message collectFields() {
        Message msg = null;
        try {
            msg = new Message();
            stdout.println("\nNew Order:");
            
            stdout.println("\nOperation:");
            stdout.println(Operation.BUY+ " - Buy");
            stdout.println(Operation.SELL + " - Sell");
            stdout.println(Operation.INFO_REQUEST + " - Info");
            stdout.println(Operation.GREETING + " - Greeting");
            
            prompt();
            
            int oper = Integer.parseInt(stdin.readLine());
            msg.put("operation", oper);
            
            if (oper == Operation.BUY || oper == Operation.SELL) {
                stdout.println("\nSymbol:");
                
                prompt();
                
                msg.put("symbol", stdin.readLine());
                
                stdout.println("\nLimit:");
                
                prompt();
                
                msg.put("limit", Double.parseDouble(stdin.readLine()));
                
                
                if (oper == Operation.BUY) {
                    stdout.println("\nValue:");
                    
                    prompt();
                    
                    msg.put("value", Double.parseDouble(stdin.readLine()));
                }
                else if (oper == Operation.SELL) {
                    stdout.println("\nQuotas:");
                    
                    prompt();
                    
                    msg.put("quotas", Double.parseDouble(stdin.readLine()));
                }
            }
            else if (oper == Operation.GREETING) {
                msg.put("greet", "Hello Market!");
            }
        }
        catch (Exception e) {
            msg = null;
        }

        return msg;
    }

    private int netxCommand() {
        int cmd = CMD_NULL;
        
        stdout.println("\nNext Command:");
        stdout.println(CMD_EXIT + " - Exit");
        stdout.println(CMD_SEND + " - Send new order");
        stdout.println(CMD_SHOW + " - Show Account Info");
        stdout.println();
        
        prompt();
        
        try {
            cmd = Integer.parseInt(stdin.readLine());
        }
        catch (NumberFormatException e) {
            System.out.println("EOF");
            cmd = CMD_NULL;
        }
        catch (Exception e) {
            cmd = CMD_NULL;
        }
        
        return cmd;
    }

    private void prompt() {
        stdout.print("$ ");
    }

    private boolean connectionOk() {
        int retries = 0;
        
        while (retries < 3) {
            try {
                clientSocket
                    = new Socket(host, port);
                
                netOut
                    = new PrintWriter(clientSocket.getOutputStream(), true);
                
                netIn
                    = new BufferedReader(
                            new InputStreamReader(
                                    clientSocket.getInputStream()));
                
                return true;
            } catch (Exception e) {
                stderr.println("Error opening client socket: "
                        + e.getMessage());
            }
            
            retries++;
        }
        
        return false;
    }

    private void cleanup() {
        try {
            if (clientSocket != null) {
                clientSocket.close();
            }
        } catch (Exception e) {
            stderr.println("Error closing client socket: " + e.getMessage());
        }
        
        clientSocket = null;
    }
}


@SuppressWarnings("serial")
class Account extends HashMap<String, Share> {
    private static Account myself = null;
    
    private double balance = 0.0;
    
    public static Account instance() {
        if (myself == null) {
            init();
        }
        
        return myself;
    }
    
    public double getBalance() {
        return this.balance;
    }

    protected Account() {
        balance = 20000 * Math.random();
        
        put("VALE5", new Share("VALE5", 1000 * Math.random()));
        put("PETR4", new Share("PETR4", 1000 * Math.random()));
        put("AMBV4", new Share("AMBV4", 1000 * Math.random()));
        put("EMBR3", new Share("EMBR3", 1000 * Math.random()));
        put("ITAU4", new Share("ITAU4", 1000 * Math.random()));
    }
    
    public static void init() {
        myself = new Account();
    }
    
    public void updateShare(String symbol, double quotas) {
        Share share = get(symbol);
        
        if (share == null) {
            share = new Share(symbol, quotas);
            put(symbol, share);
        }
        else {
            share.updQuotas(quotas);
        }
    }
    
    public void updBalance(double balance) {
        this.balance += balance;
    }
}


class Share {
    private String symbol;
    private double quotas;
    
    public Share(String symbol, double quotas) {
        this.symbol = symbol;
        this.quotas = quotas;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public String getSymbol() {
        return symbol;
    }

    public void updQuotas(double quotas) {
        this.quotas += quotas;
    }

    public double getQuotas() {
        return quotas;
    }
}
