package bolsa;


class SellOrder extends Order {

    public SellOrder(String symbol, float quota, float limit) {
        super(symbol, 0, quota, limit, 2);
    }
};
