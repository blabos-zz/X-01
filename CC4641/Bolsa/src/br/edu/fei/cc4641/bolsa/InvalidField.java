package br.edu.fei.cc4641.bolsa;

@SuppressWarnings("serial")
public class InvalidField extends Exception {
	public InvalidField(String msg, String field) {
		super("Invalid field '" + field + "' on message '" + msg + "'");
	}
}
