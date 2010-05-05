package bolsa;


class Response {

    private String  symbol;
    private int     oper;
    private float   quota;
    private float   value;
    private float   total;
    
    public Response(String s, int op, float q, float v, float t) {
        this.symbol = s;
        this.oper   = op;
        this.quota  = q;
        this.value  = v;
        this.total  = t;
    }
    
    public String   getSymbol()     {return this.symbol;    }
    public float    getValue()      {return this.value;     }
    public float    getQuota()      {return this.quota;     }
    public float    getTotal()      {return this.total;     }
    public int      getOperation()  {return this.oper;      }
    
    public String toXML() {
        return new String(
		    "<Response>\n"                                              +
		    "    <Symbol>"      + symbol            + "</Symbol>\n"     +
		    "    <Value>"       + value             + "</Value>\n"      +
		    "    <Quota>"       + quota             + "</Quota>\n"      +
		    "    <Total>"       + total             + "</Total>\n"      +
		    "    <Operation>"   + Misc.opStr(oper)  + "</Operation>\n"  +
		    "</Response>"
	    );
    }
};
