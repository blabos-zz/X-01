public class Exe07 {
    int table[][];
    int ord;
    int black;
    int white;
    
    public static void main(String args[]) {
        Exe07 instance = new Exe07();
        
        instance.init();
        instance.show();
        instance.check();
    }
    
    private void init() {
        ord     = 8;
        white   = 12;
        black   = 12;
        table   = new int[ord][ord];
        
        for (int i = 0; i < ord; i++) {
            for (int j = 0; j < ord; j++) {
                if (((i + j) % 2) == 0) {
                    table[i][j] = 0;
                }
                else {
                    table[i][j] = piece_or_empty();
                }
            }
        }
    }
    
    private void show() {
        for (int i = 0; i < ord; i++) {
            for (int j = 0; j < ord; j++) {
                System.out.print(" " + table[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }
    
    private void check() {
        for (int i = 0; i < ord; i++) {
            for (int j = 0; j < ord; j++) {
                if (is_black(i, j)) {
                    if (black_can_move(i, j)) {
                        System.out.print(" M");
                    }
                    else if (black_can_capture(i, j)) {
                        System.out.print(" C");
                    }
                    else {
                        System.out.print(" N");
                    }
                }
                else {
                    System.out.print("  ");
                }
            }
            System.out.println();
        }
        System.out.println();
    }
    
    private int piece_or_empty() {
        if (coin()) {
            if ((black > 0) && (white > 0)) {
                if (coin()) {
                    black--;
                    return 2;
                }
                else {
                    white--;
                    return 1;
                }
            }
            else if (black > 0) {
                black--;
                return 2;
            }
            else if (white > 0) {
                white--;
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    
    private static boolean coin() {
        return Math.random() > 0.5;
    }
    
    private boolean is_valid(int row, int col) {
        return (
            row >= 0 &&
            row <  8 &&
            col >= 0 &&
            col <  8
        );
    }
    
    private boolean is_empty(int row, int col) {
        return is_valid(row, col) && table[row][col] == 0;
    }
    
    private boolean is_black(int row, int col) {
        return is_valid(row, col) && table[row][col] == 2;
    }
    
    private boolean is_white(int row, int col) {
        return is_valid(row, col) && table[row][col] == 1;
    }
    
    private boolean black_can_capture(int row, int col) {
        return (
            (is_white(row + 1, col + 1) && is_empty(row + 2, col + 2)) ||
            (is_white(row + 1, col - 1) && is_empty(row + 2, col - 2))
        );
    }
    
    private boolean black_can_move(int row, int col) {
        return is_empty(row + 1, col + 1) || is_empty(row + 1, col - 1);
    }
};
