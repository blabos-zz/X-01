import java.io.*;
import java.net.*;

public class EchoServer {
    public static void main(String[] args) throws IOException {

        ServerSocket serverSocket = null;

        try {
            serverSocket = new ServerSocket(7000);
        } catch (IOException e) {
            System.out.println("Could not listen on port: 7000");
            System.exit(-1);
        }
        
        Socket clientSocket = null;
        try {
            clientSocket = serverSocket.accept();
        } catch (IOException e) {
            System.out.println("Accept failed: 4444");
            System.exit(-1);
        }
        
        PrintWriter out
            = new PrintWriter(clientSocket.getOutputStream(), true);
        
        BufferedReader in
            = new BufferedReader(
                new InputStreamReader(
                    clientSocket.getInputStream()
                )
            );
        
        String inputLine, outputLine;

        while ((inputLine = in.readLine()) != null) {	
            outputLine = inputLine;
            out.println(outputLine);
        }
        
        out.close();
        in.close();
        clientSocket.close();
        serverSocket.close();
    }
}

