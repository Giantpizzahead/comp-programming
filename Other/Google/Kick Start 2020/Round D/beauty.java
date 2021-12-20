import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class beauty {
    int N, A, B;
    long numOverlap, totalBeauty;
    ArrayList<Integer>[] children;

    beauty(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        A = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        numOverlap = 0;
        totalBeauty = 0;
        children = new ArrayList[N];
        for (int i = 0; i < N; i++) children[i] = new ArrayList<>(2);
        st = new StringTokenizer(in.readLine());
        for (int i = 1; i < N; i++) {
            children[Integer.parseInt(st.nextToken()) - 1].add(i);
        }
        Pair p = dfs(0, 0);
        p.trackA.vals.clear();
        p.trackB.vals.clear();

        // out.println(numOverlap);
        double answer = (double) totalBeauty / N - (double) numOverlap / ((long) N * N);
        out.printf("Case #%d: %.7f\n", tn, answer);
    }

    Pair dfs(int n, int d) {
        totalBeauty += d / A + 1 + d / B + 1;
        if (children[n].size() == 0) {
            // Leaf
            Pair p = new Pair(new Tracker(A), new Tracker(B));
            p.trackA.update(d);
            p.trackB.update(d);
            p.count++;
            numOverlap++;
            return p;
        }

        ArrayList<Pair> pairs = new ArrayList<>(2);
        int maxLoc = -1;
        for (int e : children[n]) {
            Pair p = dfs(e, d+1);
            if (maxLoc == -1 || pairs.get(maxLoc).count < p.count) {
                maxLoc = pairs.size();
            }
            pairs.add(p);
        }

        // Merge into largest
        Pair mergedPair = pairs.get(maxLoc);
        for (int i = 0; i < pairs.size(); i++) {
            if (i != maxLoc) mergedPair.mergeWith(pairs.get(i));
        }

        mergedPair.trackA.update(d);
        mergedPair.trackB.update(d);
        mergedPair.count++;
        numOverlap += (long) mergedPair.trackA.queryOverlap(d) * mergedPair.trackB.queryOverlap(d);
        // System.out.println(mergedPair.trackA.queryOverlap(d) * mergedPair.trackB.queryOverlap(d));
        // System.out.println(mergedPair.trackA.vals);
        return mergedPair;
    }

    class Pair {
        Tracker trackA, trackB;
        int count = 0;
        Pair(Tracker a, Tracker b) {
            trackA = a;
            trackB = b;
        }

        void mergeWith(Pair p) {
            count += p.count;
            trackA.mergeWith(p.trackA);
            trackB.mergeWith(p.trackB);
        }
    }

    class Tracker {
        TreeMap<Integer, Integer> vals;
        int mod;

        Tracker(int mod) {
            this.mod = mod;
            vals = new TreeMap<>();
        }

        void update(int depth) {
            int modDepth = depth % mod;
            vals.put(modDepth, vals.getOrDefault(modDepth, 0) + 1);
        }

        int queryOverlap(int depth) {
            int modDepth = depth % mod;
            return vals.getOrDefault(modDepth, 0);
        }

        void mergeWith(Tracker t) {
            for (Map.Entry<Integer, Integer> entry : t.vals.entrySet()) {
                int modDepth = entry.getKey() % mod;
                vals.put(modDepth, vals.getOrDefault(modDepth, 0) + entry.getValue());
            }
            t.vals.clear();
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new beauty(in, out, i);
        in.close();
        out.close();
    }
}
