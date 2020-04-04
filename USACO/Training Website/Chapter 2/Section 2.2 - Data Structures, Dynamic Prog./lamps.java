/*
ID: sunnyky1
LANG: JAVA
TASK: lamps

Solution: There are really only 16 possible final states (Each button could be pressed
or not pressed). So, try all those states, and see which ones match the given lamp
configuration. Make sure to check if the counter value would work for this button state.

Runtime: O(64 * N + N^2 * log(N) [string sorting])
*/

import java.nio.Buffer;
import java.util.*;
import java.io.*;

public class lamps {
    int N, C;
    ArrayList<String> configs;
    Lamp[] lampReqs;

    lamps() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("lamps.in"));
        N = Integer.parseInt(fin.readLine());
        C = Integer.parseInt(fin.readLine());
        StringTokenizer st = new StringTokenizer(fin.readLine());
        lampReqs = new Lamp[N];
        Arrays.fill(lampReqs, Lamp.NONE);
        int lamp;
        while (true) {
            lamp = Integer.parseInt(st.nextToken()) - 1;
            if (lamp == -2) break;
            lampReqs[lamp] = Lamp.ON;
        }
        st = new StringTokenizer(fin.readLine());
        while (true) {
            lamp = Integer.parseInt(st.nextToken()) - 1;
            if (lamp == -2) break;
            lampReqs[lamp] = Lamp.OFF;
        }
        fin.close();

        // Test each possible configuration
        configs = new ArrayList<>(16);
        for (int i = 0; i <= 15; i++) {
            testConfig(i);
        }

        configs.sort(String::compareTo);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("lamps.out")));
        configs.forEach(fout::println);
        if (configs.size() == 0) fout.println("IMPOSSIBLE");
        fout.close();
    }

    void testConfig(int i) {
        if (Integer.bitCount(i) > C || Integer.bitCount(i) % 2 != C % 2) return;
        boolean[] lamps = new boolean[N];
        Arrays.fill(lamps, true);
        for (int next = Integer.lowestOneBit(i); next != 0; i -= next, next = Integer.lowestOneBit(i)) {
            if (next == 1) for (int j = 0; j < N; j++) lamps[j] = !lamps[j];
            else if (next == 1 << 1) for (int j = 0; j < N; j+=2) lamps[j] = !lamps[j];
            else if (next == 1 << 2) for (int j = 1; j < N; j+=2) lamps[j] = !lamps[j];
            else for (int j = 0; j < N; j+=3) lamps[j] = !lamps[j];
        }

        // Check if this config works
        for (int j = 0; j < N; j++) {
            if (lampReqs[j] == Lamp.ON && !lamps[j]) return;
            else if (lampReqs[j] == Lamp.OFF && lamps[j]) return;
        }

        // It works; add to possible configs
        StringBuilder sb = new StringBuilder();
        for (boolean b : lamps) sb.append(b ? 1 : 0);
        configs.add(sb.toString());
    }

    public static void main(String[] args) throws IOException {
        new lamps();
    }
}

enum Lamp {
    NONE, ON, OFF;
}