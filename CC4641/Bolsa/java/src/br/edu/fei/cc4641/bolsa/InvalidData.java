package br.edu.fei.cc4641.bolsa;

@SuppressWarnings("serial")
public class InvalidData extends Exception {
	public InvalidData(String msg, String data) {
		super("Invalid data '" + data + "' on message '" + msg + "'");
	}
}
