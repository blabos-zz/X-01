public class Teste {
    public static void main(String args[]) {
        Mae base;
        Mae m = new Mae();
        Filha f = new Filha();
        
        base = m;
        base.m1();
        base.m2();
        
        base = f;
        base.m1();
        base.m2();
        
        f.m2();
    }
};

class Mae {
    public void m1() {
        System.out.println("Mae.m1()");
    }
    
    public static void m2() {
        System.out.println("Mae.m2()");
    }
};

class Filha extends Mae {
    public void m1() {
        System.out.println("Filha.m1()");
    }
    
    public void m2() {
        System.out.println("Filha.m2()");
    }
};
