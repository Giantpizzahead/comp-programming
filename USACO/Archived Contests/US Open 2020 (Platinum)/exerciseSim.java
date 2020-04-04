import java.util.*;
import java.io.*;

public class exerciseSim {
    int N, M;
    HashMap<Integer, Integer> numSteps;

    exerciseSim(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[N];
        used = new boolean[N];
        numSteps = new HashMap<>();
        testAllArrays(0);

        System.out.println(numSteps);

        long answer = 1;
        for (Map.Entry<Integer, Integer> entry : numSteps.entrySet()) {
            for (int i = 0; i < entry.getValue(); i++) answer = answer * entry.getKey() % M;
        }
        out.println(answer);
    }

    int[] arr;
    boolean[] used;
    void testAllArrays(int i) {
        if (i == N) {
            simulateArr();
            return;
        }
        for (int j = 0; j < N; j++) {
            if (!used[j]) {
                used[j] = true;
                arr[i] = j;
                testAllArrays(i+1);
                used[j] = false;
            }
        }
    }

    void simulateArr() {
        int steps = 0;
        int[] cows = new int[N];
        for (int i = 0; i < N; i++) cows[i] = i;
        boolean looped = false;
        while (!looped) {
            steps++;
            int[] newCows = new int[N];
            for (int i = 0; i < N; i++) newCows[arr[i]] = cows[i];
            cows = newCows;
            looped = true;
            for (int i = 0; i < N; i++) {
                if (cows[i] != i) {
                    looped = false;
                    break;
                }
            }
        }
        numSteps.put(steps, numSteps.getOrDefault(steps, 0) + 1);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("exercise.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("exercise.out")));
        new exerciseSim(in, out);
        in.close();
        out.close();
    }
}
