public class MyThread extends Thread {

    static int shrek = 0;

    MyThread(String name) {
        super(name);
    }
    
    public void run() {
        while(true) {
            //System.out.println(" Thread: " + getName());
            try {
                Thread.sleep(1);
            }
            catch(Exception e) {
                System.err.println(e);
            }
        }
    }
    
    public int getShrek() {
        return MyThread.shrek++;
    }
    
};
