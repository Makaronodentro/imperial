package first;

/**
 * Created by Makaronodentro on 21/01/2016.
 */
public class Hello {

    public static void main(String[] args) {
        // Prints "first.Hello, World" to the terminal window.
        System.out.println("first.Hello, World");

        Counter con = new Counter(20);

        for(int i = 0; i < 5; i++) con.increment();

        System.out.println(con.value());
    }
}

class Counter {
    private int count = 0;

    private static int maxcount = 256;

    public Counter(int i) /* no initialiser list */ {
        count = (i < 0) ? 0 : ((i > maxcount) ? maxcount : i);
    }

    public void increment() {
        if (count < maxcount) count++;
    }

    public void decrement() {
        if (count > 0) count--;
    }

    public int value() {
        return count;
    }
}
