public class OtherThread extends Thread {

    OtherThread(String name) {
        super(name);
    }
    
    public void run() {
        while(true) {
            System.out.println(getName() + " é Thread");
            try {
                Thread.sleep(100);
            }
            catch(Exception e) {
                System.err.println(e);
            }
        }
    }
    
};
