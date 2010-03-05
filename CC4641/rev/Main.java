import edu.fei.revisao.Foo;

public class Main {
    public static void main(String args[]) {
        Foo f = new Foo();
        
        f.setIdade(10);
        System.out.println(f.getIdade());
        char c = 65;
        System.out.println(randNames(7));
    }
    
    public static String randNames(int n) {
        String ret = "";
        
        for (int i = 0; i < n; i++) {
            ret += (char)(65 + (Math.random() * 1000) % 26);
        }
        
        return ret;
    }
};
