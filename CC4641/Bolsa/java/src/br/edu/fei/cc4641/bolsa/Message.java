package br.edu.fei.cc4641.bolsa;

import java.util.HashMap;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;


/**
 * Classe principal de mensageria. Implementa o conceito de mensagem, conforme
 * o documento messages.odt.
 * 
 * Possui a capacidade de se construir a partir de uam query-string encodada
 * com os campos necessários conforme a documentação.
 * 
 * Fornece alguns métodos sobrecarregados por comodidade e depende de alguams
 * classes de exceptions externas.
 */
@SuppressWarnings("serial")
public class Message extends HashMap<String, String> {
    protected String name;
    
    /**
     * Construtor default. apenas marca o nome da mensagem como Error
     */
    public Message() {
        setName();
    }
    
    /**
     * Construtor sobrecarregado. Constrpi uma mensagem a partir de uma query-
     * string.
     */
    public Message(String data)
    throws InvalidData, MissingRequiredField, InvalidValue {
        fromStr(data);
    }
    
    /**
     * Retorna um campo como double por conveniência.
     */
    public double asDouble(String key) {
        double ret = 0.0;
        
        try {
            ret = Double.parseDouble(get(key));
        }
        catch (Exception e) {
            ret = 0.0;
        }
        
        return ret;
    }
    
    /**
     * Retorna um campo como int por conveniência.
     */
    public int asInt(String key) {
        int ret = 0;
        
        try {
            ret = Integer.parseInt(get(key));
        }
        catch (Exception e) {
            ret = 0;
        }
        
        return ret;
    }
    
    /**
     * Retorna um campo como String por conveniência.
     */
    public String asString(String key) {
        String value = get(key);
        
        return value == null ? "" : value;
    }
    
    /**
     * Atribui/cria um cmapo a partir de um double.
     */
    public String put(String key, double value) {
        return put(key, "" + value);
    }
    
    /**
     * Atribui/cria um campo a partir de um int.
     */
    public String put(String key, int value) {
        return put(key, "" + value);
    }
    
    
    /**
     * Constroi uma mensagem a aprtir de uma query-string em UTF-8.
     */
    public void fromStr(String data)
    throws InvalidData, InvalidValue {
        if (data == null) {
            throw new InvalidData("Message", "Null data received");
        }
        
        String params[] = data.split("&");
        
        for (String param : params) {
            String values[] = param.split("=");
            
            String value = "";
            try {
                value = values.length < 2 ? "" : values[1];
                put(values[0], URLDecoder.decode(value, "UTF-8"));
            }
            catch (UnsupportedEncodingException e) {
                throw new InvalidData(name, value);
            }
        }
        
        setName();
    }
    
    /**
     * Converte uma mensagem para query-string em UTF-8.
     */
    public String toStr() {
        String ret = "";
        
        setName();
        
        for (String key : keySet()) {
            if (get(key).isEmpty()) continue;
            
            String value = "";
            try {
                value = URLEncoder.encode(get(key), "UTF-8");
            } catch (UnsupportedEncodingException e) {
                value = "Internal_Error";
            }
            ret += key + "=" + value + "&";
        }
        
        return ret;
    }
    
    /**
     * Converte uma mensagem para um texto em formato semelhante a XML, apenas
     * para depuração.
     */
    public String toXML() {
        String ret = "";
        
        setName();
        
        ret += "<" + name + ">\n";
        for (String key : keySet()) {
            try {
                if (get(key).isEmpty()) continue;
                
                ret += "    <" + key + ">" + get(key) + "</" + key + ">\n";
            }
            catch (Exception e) {
                ret += "<error>Parse Error</error>";
                break;
            }
        }
        ret += "</" + name + ">\n";
        
        return ret;
    }
    
    
    /**
     * Checa se a mensagem possui os campos básicos.
     */
    public void checkHeader() throws InvalidMessage {
        if (get("clientId") == null) {
            throw new InvalidMessage(
                    "Missing required field 'clientId' on message " + name);
        }
        
        if (get("operation") == null) {
            throw new InvalidMessage(
                    "Missing required field 'operation' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de compra válida.
     */
    public void checkBuy() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.BUY) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("symbol") == null) {
            throw new InvalidMessage(
                    "Missing required field 'symbol' on message " + name);
        }
        
        if (get("value") == null) {
            throw new InvalidMessage(
                    "Missing required field 'value' on message " + name);
        }
        
        if (get("limit") == null) {
            throw new InvalidMessage(
                    "Missing required field 'limit' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de venda válida.
     */
    public void checkSell() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.SELL) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("symbol") == null) {
            throw new InvalidMessage(
                    "Missing required field 'symbol' on message " + name);
        }
        
        if (get("quotas") == null) {
            throw new InvalidMessage(
                    "Missing required field 'quotas' on message " + name);
        }
        
        if (get("limit") == null) {
            throw new InvalidMessage(
                    "Missing required field 'limit' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de aceitação válida.
     */
    public void checkAccept() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.ACCEPT) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("reqOper") == null) {
            throw new InvalidMessage(
            "Missing required field 'reqOper' on message " + name);
        }
        
        {
            int oper = asInt("reqOper");
            if (oper != Operation.BUY || oper != Operation.SELL) {
                throw new InvalidMessage(
                        "Invalid reqOper value '" + oper
                        + "' on message " + name);
            }
        }
        
        if (get("symbol") == null) {
            throw new InvalidMessage(
                    "Missing required field 'symbol' on message " + name);
        }
        
        if (get("value") == null) {
            throw new InvalidMessage(
                    "Missing required field 'value' on message " + name);
        }
        
        if (get("quotas") == null) {
            throw new InvalidMessage(
                    "Missing required field 'quotas' on message " + name);
        }
        
        if (get("limit") == null) {
            throw new InvalidMessage(
                    "Missing required field 'limit' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de rejeição válida.
     */
    public void checkReject() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.REJECT) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("symbol") == null) {
            throw new InvalidMessage(
                    "Missing required field 'symbol' on message " + name);
        }
        
        if (get("reason") == null) {
            throw new InvalidMessage(
                    "Missing required field 'reason' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de requisição de informações do mercado válida.
     */
    public void ckeckInfoRequest() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.INFO_REQUEST) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
    }
    
    /**
     * Checa se é uma mensagem de informações do mercado válida.
     */
    public void ckeckInfoResponse() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.INFO_RESPONSE) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("info") == null) {
            throw new InvalidMessage(
                    "Missing required field 'info' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de cumprimento válida.
     */
    public void ckeckGreeting() throws InvalidMessage {
        
        {
            int oper = asInt("operation");
            if (oper != Operation.GREETING) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("greet") == null) {
            throw new InvalidMessage(
                    "Missing required field 'greet' on message " + name);
        }
    }
    
    /**
     * Checa se é uma mensagem de erro válida.
     */
    public void ckeckError() throws InvalidMessage {
        checkHeader();
        
        {
            int oper = asInt("operation");
            if (oper != Operation.ERROR) {
                throw new InvalidMessage(
                        "Invalid operation '" + Operation.asString(oper)
                        + "' on message " + name);
            }
        }
        
        if (get("error") == null) {
            throw new InvalidMessage(
                    "Missing required field 'error' on message " + name);
        }
    }
    
    /**
     * Atribui o nome da mensagem conforme a operação corrente.
     */
    private void setName() {
        try {
            name = Operation.names[asInt("operation")];
        }
        catch (IndexOutOfBoundsException e) {
            put("operation", Operation.ERROR);
            name = "Error";
        }
    }
}
