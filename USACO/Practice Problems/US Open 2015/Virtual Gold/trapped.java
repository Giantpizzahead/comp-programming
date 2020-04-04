import java.io.*;
import java.util.*;

public class trapped {
    int N, answer;
    Haybale[] haybales;
    PriorityQueue<State> pq;
    DisjointSet segmentSets;

    trapped(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        haybales = new Haybale[N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            haybales[i] = new Haybale(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }
        Arrays.sort(haybales, new Comparator<Haybale>() {
            @Override
            public int compare(Haybale o1, Haybale o2) {
                return o1.x - o2.x;
            }
        });
        for (int i = 0; i < N; i++) haybales[i].i = i;

        pq = new PriorityQueue<>(Comparator.comparingInt(x -> x.l));

        // Make segments (add two extra segments on both ends to check if Bessie escaped)
        segmentSets = new DisjointSet(N + 1);
        for (int i = 1; i < N; i++) {
            segmentSets.setXSize[i] = haybales[i].x - haybales[i-1].x;
            segmentSets.consideredXSize[i] = segmentSets.setXSize[i];
            pq.add(new State(i, segmentSets.setXSize[i]));
        }
        // Exit segment sizes don't matter
        segmentSets.setXSize[0] = 0;
        segmentSets.setXSize[N] = 0;

        // Now, sort haybales by size and begin simulation
        Arrays.sort(haybales, Comparator.comparingInt(x -> x.s));
        int haybalei = 0;
        answer = 0;
        while (!pq.isEmpty()) {
            while (haybalei != haybales.length && haybales[haybalei].s < pq.peek().l) {
                // This haybale can be broken through now; remove it by merging segments
                int newID = segmentSets.union(haybales[haybalei].i, haybales[haybalei].i+1);
                pq.add(new State(newID, segmentSets.setXSize[newID]));
                haybalei++;
            }

            // Check current segment
            State s = pq.poll();
            // System.out.println("Segment size " + s.l);
            int id = segmentSets.find(s.setID);
            if (segmentSets.setXSize[id] != s.l) {
                // State is outdated
                continue;
            }

            if (segmentSets.find(0) != id && segmentSets.find(N) != id) {
                // This segment did not reach an escape point; unescapable
                // System.out.println("answer += " + segmentSets.consideredXSize[id]);
                answer += segmentSets.consideredXSize[id];
                // Prevents overcounting
                segmentSets.consideredXSize[id] = 0;
            } else {
                // Escaped!
                segmentSets.consideredXSize[id] = 0;
            }
        }

        out.println(answer);
    }

    class State {
        int setID, l;
        State(int setID, int l) {
            this.setID = setID;
            this.l = l;
        }
    }

    class DisjointSet {
        int size;
        int[] vals, setXSize, consideredXSize;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
            setXSize = new int[size];
            consideredXSize = new int[size];
        }

        int union(int a, int b) {
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return setA;

            if (vals[setA] < vals[setB]) {
                setXSize[setA] += setXSize[setB];
                setXSize[setB] = 0;
                consideredXSize[setA] += consideredXSize[setB];
                consideredXSize[setB] = 0;
                vals[setA] += vals[setB];
                vals[setB] = setA;
                return setA;
            } else {
                setXSize[setB] += setXSize[setA];
                setXSize[setA] = 0;
                consideredXSize[setB] += consideredXSize[setA];
                consideredXSize[setA] = 0;
                vals[setB] += vals[setA];
                vals[setA] = setB;
                return setB;
            }
        }

        int find(int i) {
            if (vals[i] < 0) return i;
            else {
                int res = find(vals[i]);
                vals[i] = res;
                return res;
            }
        }
    }

    class Haybale {
        int s, x, i;
        Haybale(int s, int x) {
            this.s = s;
            this.x = x;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("trapped.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("trapped.out")));
        new trapped(in, out);
        in.close();
        out.close();
    }
}
