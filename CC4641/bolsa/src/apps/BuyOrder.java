package bolsa;


class BuyOrder extends Order {

    public BuyOrder(String symbol, float value, float limit) {
        super(symbol, value, 0, limit, 1);
    }
};
