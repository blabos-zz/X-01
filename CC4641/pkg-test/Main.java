import org.blabos.inutils.Foo;
import org.blabos.inutils.Bar;

public class Main {
    public static void main(String args[]) {
        Foo f = new Foo();
        Bar b = new Bar();
        
        f.setMsg("Hello World!!!");
        
        System.out.println(f.getMsg());
        System.out.println(b.baz());
    }
};
