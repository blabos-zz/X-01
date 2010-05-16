package br.edu.fei.cc4641.bolsa;

abstract public class Operation {
	public static final int message		= 0;
	public static final int buy			= 1;
	public static final int sell		= 2;
	public static final int response	= 3;
	public static final int info		= 4;
	public static final int greeting	= 5;
	public static final int error		= 6;
	
	public static final String name[] = {
		"Message",
		"BuyOrder",
		"SellOrder",
		"Response",
		"MarketInfo",
		"Greeting",
		"Error",
	};
}
