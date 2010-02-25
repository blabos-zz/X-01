public class Exe12 {
    public static void main(String args[]) {
        int decimal     = 0;
        int module      = 0;
        String reverse  = "";
        String binary   = "";
        
        try {
            decimal = Integer.parseInt(args[0]);
        }
        catch (Exception e) {
            usage();
            System.exit(-1);
        }
        
        do {
            reverse += (decimal % 2);
        } while ((decimal /= 2) > 0);
        
        for (int i = reverse.length() - 1; i >= 0; i--) {
            binary += reverse.charAt(i);
        }
        
        System.out.println(binary);
    }
    
    private static void usage() {
        System.out.println("\nArgumentos invalidos. Use:");
        System.out.println("    java Exe12 dec_num\n");
    }
};
