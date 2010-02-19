class Exe06 {
    public static void main(String[] args) {
        int n = 0;
        
        try {
            n = Integer.parseInt(args[0]);
        }
        catch (Exception e) {
            usage();
            System.exit(-1);
        }
        
        int[][] mat     = new int[n][n];
        int mdiag_sum   = 0;
        int sdiag_sum   = 0;
        int row_sum     = 0;
        int col_sum     = 0;
        boolean magic   = false;

        // Inicializa (objeto: passagem por referencia implicita)
        init(mat, n);
        
        // Procura nas diagonais
        for (int i = 0; i < n; i++) {
            mdiag_sum += mat[i][i];
            sdiag_sum += mat[n - i - 1][i];
        }

        if (mdiag_sum == sdiag_sum) {
            for (int i = 0; i < n; i++) {
                row_sum = col_sum = 0;
                for (int j = 0; j < n; j++) {
                    row_sum += mat[i][j];
                    col_sum += mat[j][i];
                }
                if ( (row_sum != col_sum) || (row_sum != mdiag_sum)) {
                    break;
                }
            }
            if (col_sum == mdiag_sum) magic = true;
        }

        // Mostra
        show(mat, n);

        System.out.println("Magic: " + magic);
    }
    
    private static void show(int[][] mat, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(" " + mat[i][j]);
            }
            System.out.println();
        }
    }
    
    private static void init(int[][] mat, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //mat[i][j] = 1;
                mat[i][j] = i + j;
            }
        }
    }
    
    private static void usage() {
        System.out.println("\nArgumentos invalidos. Use:");
        System.out.println("    java Exe06 mat_ord\n");
    }
}
