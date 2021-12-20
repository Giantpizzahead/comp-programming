import java.util.*;
import java.io.*;

public class billboard {
    int M, N, R, S, answer;
    final int MAX_SIZE = 300;
    boolean[][] isOff = new boolean[MAX_SIZE][MAX_SIZE];
    short[][] prefix = new short[MAX_SIZE][MAX_SIZE];
    int[] maxVertWindow = new int[MAX_SIZE];
    TreeMap<Integer, Integer> low = new TreeMap<>(), high = new TreeMap<>();

    boolean runTestCase(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        if (M == 0 && N == 0 && R == 0 && S == 0) return false;
        else if (M == 0 || N == 0) {
            out.println(0);
            out.flush();
            return true;
        }

        for (int y = 0; y < M; y++) {
            String line = in.readLine();
            for (int x = 0; x < N; x++) {
                isOff[y][x] = line.charAt(x*2) == '0';
            }
        }

        // Generate prefix sum array
        for (int y = 0; y < M; y++) {
            short sum = 0;
            for (int x = 0; x < N; x++) {
                sum += isOff[y][x] ? 1 : 0;
                prefix[y][x] = sum;
            }
        }

        answer = 0;
        findAnswer();

        out.println(answer);
        out.flush();
        return true;
    }

    void findAnswer() {
        // Try every possible x range
        // Use some heuristics to hopefully speed up answer calculation
        // The size of the largest vertical window starting at a given x can never increase,
        // so try limiting based on that
        // maxVertWindow[i] = Maximum vertical window starting at index i with last rangeSize
        for (int i = 0; i < MAX_SIZE; i++) maxVertWindow[i] = 300;
        for (int rangeSize = 1; rangeSize <= N; rangeSize++) {
            for (int x = 0; x <= N - rangeSize; x++) {
                if (maxVertWindow[x] * rangeSize <= answer) continue;
                int maxVertRange = checkRange(x, x + rangeSize - 1);
                maxVertWindow[x] = maxVertRange;
                if (maxVertRange * rangeSize > answer) {
                    answer = maxVertRange * rangeSize;
                }
            }
        }
    }

    int checkRange(int x1, int x2) {
        low.clear();
        high.clear();
        int lowSum = 0;
        int highSize = 0;
        int currTop = 0;
        int maxRange = 0;

        for (int currBot = 0; currBot < M; currBot++) {
            // System.out.println("currTop=" + currTop + ", currBot=" + currBot);
            int rowNumOff = numOff(currBot, x1, x2);
            add(high, rowNumOff);
            highSize++;

            // Keep size invariant satisfied (filled with R spare rows)
            if (highSize > R) {
                // Replace row with least # of diodes with individual spares instead
                int toReplace = pollFirst(high);
                highSize--;
                add(low, toReplace);
                lowSum += toReplace;
            }

            // Keep lowSum invariant satisfied (must be <= S to replace diodes)
            while (lowSum > S && currTop <= currBot) {
                int toRemove = numOff(currTop, x1, x2);
                if (low.containsKey(toRemove)) {
                    // Simple case: Just remove the top row from low
                    remove(low, toRemove);
                    lowSum -= toRemove;
                } else {
                    // More complex case: Remove the top row from high, and maintain size invariant
                    // Choose the row with the most # of diodes
                    remove(high, toRemove);
                    int toSwitch = pollLast(low);
                    lowSum -= toSwitch;
                    add(high, toSwitch);
                }
                currTop++;
            }

            // Track max difference between top and bottom
            maxRange = Math.max(currBot - currTop + 1, maxRange);
        }

        return maxRange;
    }

    int pollFirst(TreeMap<Integer, Integer> map) {
        Map.Entry<Integer, Integer> result = map.firstEntry();
        if (result.getValue() == 1) map.remove(result.getKey());
        else map.put(result.getKey(), result.getValue() - 1);
        return result.getKey();
    }

    int pollLast(TreeMap<Integer, Integer> map) {
        Map.Entry<Integer, Integer> result = map.lastEntry();
        if (result.getValue() == 1) map.remove(result.getKey());
        else map.put(result.getKey(), result.getValue() - 1);
        return result.getKey();
    }

    void add(TreeMap<Integer, Integer> map, int v) {
        map.put(v, map.getOrDefault(v, 0) + 1);
    }

    void remove(TreeMap<Integer, Integer> map, int v) {
        int mapEntry = map.get(v);
        if (mapEntry == 1) map.remove(v);
        else map.put(v, mapEntry - 1);
    }

    int numOff(int i, int x1, int x2) {
        return prefix[i][x2] - ((x1 == 0) ? 0 : prefix[i][x1-1]);
    }

    billboard() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        boolean running = true;
        while (running) running = runTestCase(in, out);
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new billboard();
    }
}
