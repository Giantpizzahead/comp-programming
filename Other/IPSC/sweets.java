import java.util.*;
import java.io.*;

public class sweets {
    int T, R, C;
    char[][] matrix;

    sweets() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("ipsc2012/a2.in"));
        PrintWriter fout = new PrintWriter("a.out");
        StringTokenizer st = new StringTokenizer(fin.readLine());
        T = Integer.parseInt(st.nextToken());
        fin.readLine();
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(fin.readLine());
            R = Integer.parseInt(st.nextToken());
            C = Integer.parseInt(st.nextToken());
            matrix = new char[R][];
            for (int j = 0; j < R; j++) {
                matrix[j] = fin.readLine().toCharArray();
            }
            fin.readLine();

            // Find candies by checking top left corner
            int numCandies = 0;
            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    if (x < C - 2) {
                        // Horizontal candy
                        if (matrix[y][x] == '>' && matrix[y][x+1] == 'o' && matrix[y][x+2] == '<') numCandies++;
                    }
                    if (y < R - 2) {
                        // Vertical candy
                        if (matrix[y][x] == 'v' && matrix[y+1][x] == 'o' && matrix[y+2][x] == '^') numCandies++;
                    }
                }
            }

            fout.println(numCandies);
        }
        fin.close();
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new sweets();
    }
}
