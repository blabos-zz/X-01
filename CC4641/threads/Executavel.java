class Executaval {
    public static void main(String args[]) {
    
        Bar b = new Bar(0);
        
        Foo f1 = new Foo("Arnon", 2, "+", b);
        f1.start();
        
        Foo f2 = new Foo("Poneis", 1, "-", b);
        f2.start();
    }
}
