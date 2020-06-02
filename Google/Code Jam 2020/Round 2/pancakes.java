import java.util.*;
import java.io.*;

public class pancakes {
    boolean flipped = false;
    int numServed = 0;
    long L, R;

    pancakes(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        L = Long.parseLong(st.nextToken());
        R = Long.parseLong(st.nextToken());
        if (R > L) {
            flipped = true;
            long temp = L;
            L = R;
            R = temp;
        }

        // Now L >= R
        // Find first time where L is just greater than R (alternation begins)
        int low = 0, high = 1500000000;
        while (low < high) {
            int mid = (int) (((long) low + high + 1) / 2);
            if (L - sumFrom1(mid) < R) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }

        numServed += low;
        L -= sumFrom1(numServed);

        if (L == R) flipped = false;

        // Now, calculate alternation sum
        // Find time where L is just greater than 0, and time where R is just greater than 0
        int lcount, rcount;
        low = 0;
        high = 1000000000;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (L - altSumFromOffset(mid, numServed + 1) < 0) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        lcount = low;
        low = 0;
        high = 1000000000;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (R - altSumFromOffset(mid, numServed + 2) < 0) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        rcount = low;

        // Just in case...
        if (rcount > lcount) rcount = lcount;
        if (lcount > rcount + 1) lcount = rcount + 1;

//        System.out.println("alt: " + numServed);
//        System.out.println("lcount: " + lcount);
//        System.out.println("rcount: " + rcount);

        L -= altSumFromOffset(lcount, numServed + 1);
        R -= altSumFromOffset(rcount, numServed + 2);
        numServed += lcount + rcount;

        if (!flipped) out.println("Case #" + tn + ": " + numServed + " " + L + " " + R);
        else out.println("Case #" + tn + ": " + numServed + " " + R + " " + L);
    }

    long altSumFromOffset(int count, int offset) {
        return (long) offset * count + sumFrom1(count - 1) * 2;
    }

    long sumFrom1(int n) {
        return (long) n * (n + 1) / 2;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new pancakes(in, out, i);
        in.close();
        out.close();
    }
}
