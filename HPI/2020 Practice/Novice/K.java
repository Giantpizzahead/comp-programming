import java.io.*;
import java.util.*;

public class K {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());
        HashMap<Long, Integer> locs = new HashMap<>();
        for (int i = 0; i < N; i++) {
            long v = Long.parseLong(in.readLine());
            locs.put(v, locs.getOrDefault(v, 0) + 1);
        }

        ArrayList<Integer> entries = new ArrayList<>();
        for (Map.Entry<Long, Integer> entry : locs.entrySet()) {
            entries.add(entry.getValue());
        }
        Collections.sort(entries);
        int answer = 0;
        for (int i = 0; i < Math.min(K, entries.size()); i++) {
            answer += entries.get(entries.size() - 1 - i);
        }
        System.out.println(answer);
    }
}
