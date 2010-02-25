public class Exe04 {
    public static void main(String args[]) {
        int first, last, sqrt;
        
        for (int i = 1000; i <= 9999; i++) {
            sqrt    = (int)Math.floor(Math.sqrt(i));
            first   = i / 100;
            last    = i % 100;
            
            if (((sqrt * sqrt) == i) && (sqrt == (first + last))) {
                System.out.println(
                    "Raiz de " + i + " = " + sqrt + " = " + first + " + "
                    + last
                );
            }
        }
    }
};
