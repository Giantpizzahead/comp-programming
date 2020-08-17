import java.util.*;
import java.io.*;

public class gcdcomp {
    int N;
    ArrayList<Integer> isOdd, isEven;
    int[] arr;

    gcdcomp(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken()) * 2;
        isOdd = new ArrayList<>();
        isEven = new ArrayList<>();
        st = new StringTokenizer(in.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
            if (arr[i] % 2 == 0) isEven.add(i);
            else isOdd.add(i);
        }

        // Remove two elements
        if (isOdd.size() % 2 == 1) {
            // Both are odd
            isOdd.remove(0);
            isEven.remove(0);
        } else {
            // Both are even
            if (isOdd.size() != 0) {
                isOdd.remove(0);
                isOdd.remove(0);
            } else {
                isEven.remove(0);
                isEven.remove(0);
            }
        }
        // System.out.println(isOdd);
        // System.out.println(isEven);

        // Pair even-even and odd-odd
        for (int i = 0; i < isOdd.size(); i += 2) {
            out.printf("%d %d\n", isOdd.get(i)+1, isOdd.get(i+1)+1);
        }
        for (int i = 0; i < isEven.size(); i += 2) {
            out.printf("%d %d\n", isEven.get(i)+1, isEven.get(i+1)+1);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new gcdcomp(in, out);
        in.close();
        out.close();
    }
}
