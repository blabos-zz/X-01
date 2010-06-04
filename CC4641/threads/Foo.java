class Foo extends Thread {
    private int secs = 0;
    private String operation = "+";
    
    private static int data = 0;
    
    Bar sharedObj = null;
    
    
    public Foo(String name, int s, String op, Bar shared) {
        super(name);
        this.secs = s;
        this.operation = op;
        this.sharedObj = shared;
    }
    
    public void run() {
        if (operation == "+") {
            sharedObj.doit(+1);
        }
        else {
            sharedObj.doit(-1);
        }
    }
    
    
}

class Bar {
    public int data = 0;
    
    public Bar(int a) {
        data = a;
    }
    
    void doit(int num) {
        int count = 10;
        while (count-- > 0) {
            synchronized(this) {
                data += num;
            }
            System.out.println(num + " data = " + data);
            try {
                Thread.sleep(1000 * 1);
            }
            catch (Exception e) {}
        }
    }
}
