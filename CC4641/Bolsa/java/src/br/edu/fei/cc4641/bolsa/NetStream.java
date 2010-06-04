package br.edu.fei.cc4641.bolsa;

import java.io.*;
import java.net.*;

/**
 * Encapsula o acesso aos sockets. Este componente foi adicioando para que se
 * pudesse chavear facilmente entre as formas de transmissão serializada e
 * query-string.
 * 
 * Fornece os métodos readMessage e writeMessage para recepção e envio de
 * mensagens, respectivamente.
 *
 */
public final class NetStream {
    private Socket socket                   = null;
    private Config conf                     = null;
    
    private PrintWriter queryOut            = null;
    private BufferedReader queryIn          = null;

    private ObjectOutputStream serialOut    = null;
    private ObjectInputStream serialIn      = null;
    
    private PrintStream stdout              = null;
    private PrintStream stderr              = null;
    
    public NetStream(Socket socket, Config conf)
    throws IOException {
        this.socket = socket;
        this.conf   = conf;
        stdout      = System.out;
        stderr      = System.err;
        
        if (this.conf.getProtocol() == Protocol.PROTO_QUERYSTRING) {
            queryOut
                = new PrintWriter(
                        this.socket.getOutputStream(), true);
        
            queryIn
                = new BufferedReader(
                        new InputStreamReader(
                                this.socket.getInputStream()));
        }
        else {
            serialOut
                = new ObjectOutputStream(
                        this.socket.getOutputStream());
        
            serialIn
                = new ObjectInputStream(
                        this.socket.getInputStream());
        }
    }
    
    public Message readMessage() {
        Message msg = null;
        
        try {
            if (conf.getProtocol() == Protocol.PROTO_QUERYSTRING) {
                msg = new Message(queryIn.readLine());
            }
            else {
                msg = (Message)serialIn.readObject();
            }
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
            msg = null;
        }
        
        return msg;
    }
    
    public void writeMessage(Message msg) {
        try {
            if (conf.getProtocol() == Protocol.PROTO_QUERYSTRING) {
                queryOut.println(msg.toStr());
            }
            else {
                serialOut.writeObject(msg);
            }
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    }

    public void cleanup() {
        try {
            if (socket != null) {
                socket.close();
                socket = null;
            }
        }
        catch (Exception e) {
            stderr.println(e.getMessage());
        }
    }
}
