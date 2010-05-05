public class Main {
    
    public static void main(String args[]) {
        MyThread m = new MyThread("Mamae");
        m.start();
        
        MyThread p = new MyThread("Papai");
        p.start();
    }
};
