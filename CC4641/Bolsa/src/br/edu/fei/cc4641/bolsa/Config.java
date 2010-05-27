package br.edu.fei.cc4641.bolsa;

public class Config {
    private int protocol        = Protocol.PROTO_QUERYSTRING;
    private String serverHost   = "localhost";
    private int serverPort      = -1;
    private int listenPort      = -1;
    
    public Config(String serverHost, int serverPort, int listenPort,
            int protocol) {
        setServerHost(serverHost);
        setServerPort(serverPort);
        setListenPort(listenPort);
        setProtocol(protocol);
    }

    public void setProtocol(int protocol) {
        this.protocol = protocol;
    }

    public int getProtocol() {
        return protocol;
    }

    public void setServerHost(String serverHost) {
        this.serverHost = serverHost;
    }

    public String getServerHost() {
        return serverHost;
    }

    public void setServerPort(int serverPort) {
        this.serverPort = serverPort;
    }

    public int getServerPort() {
        return serverPort;
    }

    public void setListenPort(int listenPort) {
        this.listenPort = listenPort;
    }

    public int getListenPort() {
        return listenPort;
    }
}
