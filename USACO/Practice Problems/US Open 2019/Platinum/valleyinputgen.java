import java.util.*;
import java.io.*;

public class valleyinputgen {
    public static void main(String[] args) throws IOException {
        String[] board = {
                "111111111",
                "144444441",
                "142222241",
                "142222241",
                "142232241",
                "142222241",
                "142222241",
                "144444441",
                "111111111"
        };

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("valleys.in")));
        fout.println(board.length);
        int index = 1;
        for (int y = 0; y < board.length; y++) {
            for (int x = 0; x < board.length; x++) {
                fout.printf("%c%03d ", board[y].charAt(x), index);
                index++;
            }
            fout.println();
        }
        fout.close();
    }
}
