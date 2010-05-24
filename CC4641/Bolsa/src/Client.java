import java.io.*;
import java.net.*;

import br.edu.fei.cc4641.bolsa.*;

public class Client {
public static final int NULL= -1;
public static final int EXIT= 0;
public static final int SEND= 1;

public static final int MAX_RETRIES= 3;

private static String host= "localhost";
private static int port= 7080;
private static int retries= 0;

private static Socket client= null;
    private static PrintWriter out= null;
    private static BufferedReader in= null;
    
    private static BufferedReader stdin= null;
    private static PrintStream stdout= null;
    private static PrintStream stderr= null;

private static Message collect() {
Message msg = null;

try {
msg = new Message();

stdout.println("\nNew Order:");
//stdout.println("clientId:");
//prompt();
//msg.put("clientId", stdin.readLine());

stdout.println("Operation:");
stdout.println(Operation.BUY+ " - Buy");
stdout.println(Operation.SELL + " - Sell");
stdout.println(Operation.INFO_REQUEST + " - Info");
stdout.println(Operation.GREETING + " - Greeting");

prompt();
int oper = Integer.parseInt(stdin.readLine());
msg.put("operation", oper);

if (oper == Operation.BUY || oper == Operation.SELL) {
stdout.println("Symbol:");
prompt();
msg.put("symbol", stdin.readLine());

stdout.println("Limit:");
prompt();
msg.put("limit", Double.parseDouble(stdin.readLine()));

if (oper == Operation.BUY) {
stdout.println("Value:");
prompt();
msg.put("value", Double.parseDouble(stdin.readLine()));
}
else if (oper == Operation.SELL) {
stdout.println("Quotas:");
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

private static int command() {
int cmd = EXIT;

stdout.println("\nNext Command:");
stdout.println(EXIT + " - Exit");
stdout.println(SEND + " - Send new order");
prompt();
try {
cmd = Integer.parseInt(stdin.readLine());
}
catch (NumberFormatException e) {
System.out.println("EOF");
}
catch (Exception e) {
cmd = NULL;
}

return cmd;
}

public static void main(String[] args) {
int cmd = NULL;
Message msg = null;
stdin= new BufferedReader(new InputStreamReader(System.in));
stdout= System.out;
stderr= System.err;

while (cmd != EXIT) {
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
stdout.println();
}

private static void prompt() {
stdout.print("$ ");
}

private static Message receive() {
Message msg = null;
String line = "";
try {
line = in.readLine();
msg = new Message(line);
}
catch (Exception e) {
stderr.println(e.getMessage());
}

return msg;
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
        
        try { Thread.sleep(1000); }
        catch (Exception e) { System.err.println(e); }
            
        retries++;
return false;
}

private static void send(Message msg) {
try {
out.println(msg.toStr());
}
catch (Exception e) {
stderr.println(e.getMessage());
}
}

private static void show(Message msg) {
if (msg != null) {
stdout.println("\nMarket Response:");

int oper = msg.asInt("operation");

if (oper == Operation.INFO_RESPONSE) {
showInfo(msg);
}
else if (oper == Operation.GREETING) {
showGreeting(msg);
}
else {
stdout.println(msg.toXML());
}
}
else stdout.println("Invalid response received");
}

private static void showGreeting(Message msg) {
String greet = msg.asString("greet");
stdout.println(greet);
}

private static void showInfo(Message msg) {
MarketInfo info = new MarketInfo(msg);
info.print();
}

}
