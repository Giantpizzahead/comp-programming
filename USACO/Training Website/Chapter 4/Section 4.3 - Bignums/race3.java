/*
Solution: For each point, try removing it to see if participants can still
reach the finish (if they can't, it is unavoidable). If the point is
unavoidable, do 2 DFSs from the point; one forward, and one backward. If the
# of nodes visited from those DFSs is equal to the # of nodes + 1, then the
point is also a splitting point.
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class race3 {
    int N;

    race3(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("race3.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("race3.out")));
        new race3(in, out);
        in.close();
        out.close();
    }
}