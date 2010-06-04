package br.edu.fei.cc4641.bolsa;

/**
 * Exceção disparada quando uma campo requerido está faltando.
 */
@SuppressWarnings("serial")
public class MissingRequiredField extends Exception {
    public MissingRequiredField(String msg, String field) {
        super("Missing required field '" + field
                + "' on message '" + msg + "'");
    }
}
