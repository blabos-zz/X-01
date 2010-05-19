package br.edu.fei.cc4641.bolsa;

@SuppressWarnings("serial")
public class InvalidMessage extends Exception {
	public InvalidMessage(String reason) {
		super(reason);
	}
}
