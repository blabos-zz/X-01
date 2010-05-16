package br.edu.fei.cc4641.bolsa;

@SuppressWarnings("serial")
public class MissingRequiredField extends Exception {
	public MissingRequiredField(String msg, String field) {
		super("Missing required field '" + field
				+ "' on message '" + msg + "'");
	}
}
