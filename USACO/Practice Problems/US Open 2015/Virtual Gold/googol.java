import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class googol {
    BufferedReader in;
    // Binary search on N
    BigInteger low = BigInteger.ONE;
    BigInteger high;
    Deque<Boolean> searchPath;

    googol() throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        searchPath = new LinkedList<>();
        search(1);
        in.close();
        System.out.println("Answer " + low.toString());
    }

    void search(int id) throws IOException {
        // Check for left neighbor
        query(id);
        if (queryL != 0) {
            // More left neighbors!
            low = low.add(low);
            search(queryL);
        } else {
            // Ends here
            high = low.add(low).subtract(BigInteger.ONE);
            // System.out.println("start " + low + " " + high);
            return;
        }

        // Narrow down the binary search by following the search path
        searchPath.addFirst(true);
        boolean found = true;
        for (boolean goRight : searchPath) {
            query(id);
            if (goRight) {
                if (queryR == 0) {
                    found = false;
                    break;
                } else id = queryR;
            } else {
                if (queryL == 0) {
                    found = false;
                    break;
                } else id = queryL;
            }
        }

        BigInteger mid = low.add(high).add(BigInteger.ONE).divide(BigInteger.valueOf(2));
        if (found) {
            // Binary search on higher values
            low = mid;
        } else {
            // Lower values; change search path
            searchPath.removeFirst();
            searchPath.addFirst(false);
            high = mid.subtract(BigInteger.ONE);
        }
        // System.out.println(low + " " + high);
    }

    int queryL, queryR;
    void query(int id) throws IOException {
        System.out.println(id);
        StringTokenizer st = new StringTokenizer(in.readLine());
        queryL = Integer.parseInt(st.nextToken());
        queryR = Integer.parseInt(st.nextToken());
    }

    public static void main(String[] args) throws IOException {
        new googol();
    }
}
