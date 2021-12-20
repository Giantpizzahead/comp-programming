import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class tester {
    public static void main(String[] args) throws IOException {
        PrintWriter out = new PrintWriter(new FileWriter("test.in"));
        out.println(5);
        for (int a = 0; a < 5; a++) {
            out.println("500000 1 1");
            for (int i = 1; i < 500000; i++) {
                if (i != 1) out.print(' ');
                out.print(i);
            }
            out.println();
        }
        out.close();
    }
}
