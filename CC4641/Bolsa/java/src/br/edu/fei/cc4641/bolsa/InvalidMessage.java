package br.edu.fei.cc4641.bolsa;

/**
 * Exception lançada quando uma mensagem inválida é detectada.
 */
@SuppressWarnings("serial")
public class InvalidMessage extends Exception {
    public InvalidMessage(String reason) {
        super(reason);
    }
}
