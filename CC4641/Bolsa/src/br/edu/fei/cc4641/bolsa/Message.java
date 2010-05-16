package br.edu.fei.cc4641.bolsa;

import java.util.HashMap;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;


@SuppressWarnings("serial")
public class Message extends HashMap<String, String> {
	protected String name;
	
	public Message() {
		name = "Message";
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
			} catch (UnsupportedEncodingException e) {
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
		
		ret += "<" + name + ">\n";
		for (String key : keySet()) {
			if (get(key).isEmpty()) continue;
			
			ret += "    <" + key + ">" + get(key) + "</" + key + ">\n";
		}
		ret += "</" + name + ">\n";
		
		return ret;
	}
	
	
	/**
	 * Validates message header.
	 * @throws MissingRequiredField When missing a required field
	 */
	public void validateHeader() throws MissingRequiredField {
		if (get("clientId") == null) {
			throw new MissingRequiredField(name, "clientId");
		}
		
		if (get("brokerId") == null) {
			throw new MissingRequiredField(name, "brokerId");
		}
		
		if (get("operation") == null) {
			throw new MissingRequiredField(name, "operation");
		}
	}
	
	/**
	 * Validates a Buy Order.
	 * @throws MissingRequiredField When missing a requires field
	 * @throws InvalidValue When a invalid value is found
	 */
	public void validateBuy() throws MissingRequiredField, InvalidValue {
		validateHeader();
		
		if (asInt("operation") != Operation.buy) {
			throw new InvalidValue(name, "operation", asString("operation"));
		}
		
		if (get("symbol") == null) {
			throw new MissingRequiredField(name, "symbol");
		}
		
		if (get("value") == null) {
			throw new MissingRequiredField(name, "value");
		}
		
		if (get("limit") == null) {
			throw new MissingRequiredField(name, "limit");
		}
	}
	
	/**
	 * Validates a Sell Order.
	 * @throws MissingRequiredField When missing a requires field
	 * @throws InvalidValue When a invalid value is found
	 */
	public void validateSell() throws MissingRequiredField, InvalidValue {
		validateHeader();
		
		if (asInt("operation") != Operation.sell) {
			throw new InvalidValue(name, "operation", asString("operation"));
		}
		
		if (get("symbol") == null) {
			throw new MissingRequiredField(name, "symbol");
		}
		
		if (get("quota") == null) {
			throw new MissingRequiredField(name, "quota");
		}
		
		if (get("limit") == null) {
			throw new MissingRequiredField(name, "limit");
		}
	}
	
	/**
	 * Validates a Market Info Order.
	 * @throws MissingRequiredField When missing a requires field
	 * @throws InvalidValue When a invalid value is found
	 */
	public void validateInfo() throws InvalidValue, MissingRequiredField {
		validateHeader();
		
		if (asInt("operation") != Operation.info) {
			throw new InvalidValue(name, "operation", asString("operation"));
		}
	}
	
	/**
	 * Automatically sets message name using operation number.
	 * @throws InvalidValue When a invalid operation is found
	 */
	private void setName() throws InvalidValue {
		try {
			name = Operation.name[asInt("operation")];
		}
		catch (IndexOutOfBoundsException e) {
			name = "Message";
			throw new InvalidValue(name, "operation", asString("operation"));
		}
	}
}
