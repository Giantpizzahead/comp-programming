import java.util.*;
import java.io.*;

public class museum {
    int N;

    museum(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        int[] answer = solve(N);
        Arrays.stream(answer).forEach(out::println);
    }

    int[] solve(int n) {
        if (n == 1) return new int[] {1};
        // Divide into odd and even vases
        int numOdd = (n + 1) / 2, numEven = n / 2;
        int[] oddSolve = solve(numOdd), evenSolve = solve(numEven);
        int[] answer = new int[n];
        for (int i = 0; i < numOdd; i++) answer[i] = oddSolve[i] * 2 - 1;
        for (int i = numOdd; i < n; i++) answer[i] = evenSolve[i - numOdd] * 2;
        return answer;
    }

    public static void main(String[] args) throws IOException {
        for (int t = 1; t <= 5; t++) {
            BufferedReader in = new BufferedReader(new FileReader("museum." + t + ".in"));
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("museum." + t + ".out")));
            new museum(in, out);
            in.close();
            out.close();
        }
    }
}
