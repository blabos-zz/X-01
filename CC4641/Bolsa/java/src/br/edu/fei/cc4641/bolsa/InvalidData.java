package br.edu.fei.cc4641.bolsa;

/**
 * Exception lançada quando um dado inválido, mal encodado ou uma mensagem
 * não instanciada é encontrada onde se esperava dados válidos.
 */
@SuppressWarnings("serial")
public class InvalidData extends Exception {
	public InvalidData(String msg, String data) {
		super("Invalid data '" + data + "' on message '" + msg + "'");
	}
}
