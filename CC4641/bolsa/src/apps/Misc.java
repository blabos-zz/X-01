package bolsa;


class Misc {
    public static String opStr(int op) {
        return op == 1 ? "Buy" : op == 2 ? "Sell" : "Unknown";
    }
};
