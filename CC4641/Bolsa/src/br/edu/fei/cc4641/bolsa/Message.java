package br.edu.fei.cc4641.bolsa;

import java.util.HashMap;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;


@SuppressWarnings("serial")
public class Message extends HashMap<String, String> {
    protected String name;
    
    public Message() {
        setName();
    }
    
    public Message(String data)
    throws InvalidData, MissingRequiredField, InvalidValue {
        fromStr(data);
    }
    
    /**
     * Returns a field value converted for convenience.
     * @param key Field name
     * @return Field value as double
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
     * Returns a field value converted for convenience.
     * @param key Field name
     * @return Field value as integer
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
     * Returns a field value converted for convenience.
     * @param key Field name
     * @return Field name as String
     */
    public String asString(String key) {
        return get(key);
    }
    
    /**
     * Accepts a double as value.
     * @param key Field name
     * @param value Field value
     * @return Last value of field
     */
    public String put(String key, double value) {
    return put(key, "" + value);
    }
    
    /**
     * Accepts a integer as value.
     * @param key Field name
     * @param value Field value
     * @return Last value of field
     */
    public String put(String key, int value) {
        return put(key, "" + value);
    }
    
    
    /**
     * Builds a message from a UTF-8 query string.
     * @param data Query string
     * @throws InvalidData When cannot decode values
     * @throws InvalidValue When a invalid value is found
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
     * Converts a message to a query string.
     * @return Query string
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
     * Converts a message to a XML-like string (for display purposes).
     * @return XML like string
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
    
    public void ckeckGreeting() throws InvalidMessage {
        checkHeader();
        
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
