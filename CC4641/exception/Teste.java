public class Teste {
    public static void main(String args[]) {
        
    }
    
    public void nullTeste(int num) throws IOException {
        if (num == 0) {
            throw new NullPointerException();
        }
        else {
            throw new Exception();
        }
    }
};
