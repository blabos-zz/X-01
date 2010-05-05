package bolsa;


class Order {
    protected String symbol;
    protected float value;
    protected float quota;
    protected float limit;
    protected int oper;

    protected Order(String symbol, float value, float quota, float limit,
                    int op) {
        this.symbol = symbol;
        this.value  = value;
        this.quota  = quota;
        this.limit  = limit;
        this.oper   = op;
    }

    public String   getSymbol()     {return this.symbol;    }
    public float    getValue()      {return this.value;     }
    public float    getQuota()      {return this.quota;     }
    public float    getLimit()      {return this.limit;     }
    public int      getOperation()  {return this.oper;      }

    public String toXML() {
	    return new String(
		    "<Order>\n"                                                 +
		    "    <Symbol>"      + symbol            + "</Symbol>\n"     +
		    "    <Value>"       + value             + "</Value>\n"      +
		    "    <Quota>"       + quota             + "</Quota>\n"      +
		    "    <Limit>"       + limit             + "</Limit>\n"      +
		    "    <Operation>"   + Misc.opStr(oper)  + "</Operation>\n"  +
		    "</Order>"
	    );
    }
};
