package br.edu.fei.cc4641.bolsa;

@SuppressWarnings("serial")
public class InvalidValue extends Exception {
	public InvalidValue(String msg, String field, String value) {
		super("Invalid value '" + value
				+ "' in field '"  + field
				+ "' on message '" + msg + "'");
	}
}
