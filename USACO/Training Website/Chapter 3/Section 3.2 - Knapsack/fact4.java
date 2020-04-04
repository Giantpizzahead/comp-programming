/*
ID: sunnyky1
LANG: JAVA
TASK: fact4

Solution: All you need to keep track of is the 1st nonzero digit from
right to left. So, after each multiplication, remove all 0 digits from
the right, and take only the 1st digit after that (%10).

Actually, you probably need to keep at least 4 digits since the max N is
4 digits long.

Runtime: O(~4N)
*/

import java.util.*;
import java.io.*;

public class fact4 {
    int N;

    fact4() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("fact4.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        fin.close();

        PrintWriter fout = new PrintWriter("fact4.out");
        fout.println(factorial(N) % 10);
        fout.close();
    }

    long factorial(int n) {
        if (n == 1) return 1;
        else {
            long result = n * factorial(n-1);
            // Remove all trailing zeros
            while (result % 10 == 0) {
                result /= 10;
            }
            // Keep a couple digits
            result %= 1000000;
            return result;
        }
    }

    public static void main(String[] args) throws IOException {
        new fact4();
    }
}