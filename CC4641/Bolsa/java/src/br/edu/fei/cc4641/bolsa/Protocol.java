package br.edu.fei.cc4641.bolsa;

/**
 * Fornece duas constantes para indicar o 'protocolo' usado na comunicação. Os
 * protocolos disponíveis são PROTO_QUERYSTRING e PROTO_SERIALIZED.
 * 
 * Na versão query-string as mensagens são transformadas em texto no formato
 * chave/valor e codificados como em uma url. Já na versão serializada, as
 * mensagens são serializadas no formato padrão do Java para serem então
 * transmitidas.
 * 
 * Usualmente as aplicações que 'falam' query-string utilizam as portas 70*0,
 * enquanto que as aplicações que 'falam' serializado utilizam portas 70*1.
 */
public final class Protocol {
    public static final int PROTO_QUERYSTRING   = 1;
    public static final int PROTO_SERIALIZED    = 2;
}
