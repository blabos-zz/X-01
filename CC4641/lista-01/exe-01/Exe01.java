class Exe01 {
    public static void main(String args[]) {
        int num     = 0;
        int mid     = 0;
        int prev    = 0;
        int next    = 0;
        
        try {
            num = Integer.parseInt(args[0]);
        }
        catch (Exception e) {
            System.out.println("Exception");
            System.exit(-1);
        }
        
        mid = middle_factor(num);
        prev = mid - 1;
        next = mid + 1;
        
        if (num == (prev * mid * next)) {
            System.out.println(
                num + " is triangular (" + prev + " * " + mid + " * " +
                next + ")"
            );
        }
        else {
            System.out.println( num + " isn't triangular");
        }
    }
    
    private static int middle_factor(int num) {
        return (int)Math.ceil(Math.pow(num, 1.0/3));
    }
};
