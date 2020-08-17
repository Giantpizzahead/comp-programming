import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class easynumber {
    int A, B, C;
    ArrayList<Integer>[] primeFacts;

    easynumber(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        A = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        primeFacts = new ArrayList[101];
        for (int i = 1; i <= 100; i++) {
            primeFacts[i] = getFactorization(i);
        }

        long sum = 0;
        HashMap<Integer, Integer> numFactors = new HashMap<>();
        for (int a = 1; a <= A; a++) {
            for (int b = 1; b <= B; b++) {
                for (int c = 1; c <= C; c++) {
                    numFactors.clear();
                    for (int f : primeFacts[a]) {
                        numFactors.put(f, numFactors.getOrDefault(f, 0) + 1);
                    }
                    for (int f : primeFacts[b]) {
                        numFactors.put(f, numFactors.getOrDefault(f, 0) + 1);
                    }
                    for (int f : primeFacts[c]) {
                        numFactors.put(f, numFactors.getOrDefault(f, 0) + 1);
                    }
                    long numDivisors = 1;
                    for (int e : numFactors.values()) {
                        numDivisors *= (e+1);
                    }
                    sum = (sum + numDivisors) % 1000000007;
                }
            }
        }
        out.println(sum);
    }

    ArrayList<Integer> getFactorization(int x) {
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 2; i <= x; i++) {
            while (x % i == 0) {
                x /= i;
                res.add(i);
            }
        }
        return res;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new easynumber(in, out);
        in.close();
        out.close();
    }
}
