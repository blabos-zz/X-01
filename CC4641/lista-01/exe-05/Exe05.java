class Exe05 {
    public static void main(String[] args) {
        int base        = 0;
        int sub         = 0;
        int mask        = 1;
        int tmp         = 0;
        boolean found   = false;
        
        try {
            base    = Integer.parseInt(args[0]);
            sub     = Integer.parseInt(args[1]);
            tmp     = sub;
        }
        catch (Exception e) {
            usage();
            System.exit(-1);
        }

        do {
            mask *= 10;
        } while ((tmp /= 10) != 0);

        while (base >= mask / 10) {
            tmp = base % mask;
            if ((base == sub) || (tmp == sub)) {
                found = true;
                break;
            }
            base /= 10;
        }

        System.out.println("Subnum found: " + found);
    }
    
    private static void usage() {
        System.out.println("\nArgumentos invalidos. Use:");
        System.out.println("    java Exe05 basenum subnum\n");
    }
}
