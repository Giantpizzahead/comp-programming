/*
Solution: The pies form a bipartite graph, so start from the pies that will end the exchange, and BFS from there. Once
a pie has been visited, remove it from the TreeSet so that it won't take up more runtime.

Runtime: O(2N * log(2N))
*/

import java.util.*;
import java.io.*;

public class piepie {
    int N, D;
    int[] answers;
    Queue<Pie> bessieQ, elsieQ;
    TreeSet<Pie> bessiePies, elsiePies;

    piepie() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("piepie.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        answers = new int[N];
        Arrays.fill(answers, -1);
        bessiePies = new TreeSet<>((a, b) -> {
            if (a.e == b.e) return a.origI - b.origI;
            else return a.e - b.e;
        });
        elsiePies = new TreeSet<>((a, b) -> {
            if (a.b == b.b) return a.origI - b.origI;
            else return a.b - b.b;
        });
        bessieQ = new LinkedList<>();
        elsieQ = new LinkedList<>();
        int b, e;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            b = Integer.parseInt(st.nextToken());
            e = Integer.parseInt(st.nextToken());
            if (e == 0) {
                // This pie could end the exchange
                answers[i] = 1;
                Pie np = new Pie(b, e, i);
                np.cost = 1;
                bessieQ.add(np);
            } else bessiePies.add(new Pie(b, e, i));
        }
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            b = Integer.parseInt(st.nextToken());
            e = Integer.parseInt(st.nextToken());
            if (b == 0) {
                // This pie could end the exchange
                Pie np = new Pie(b, e, i);
                np.cost = 1;
                elsieQ.add(np);
            } else elsiePies.add(new Pie(b, e, i));
        }
        fin.close();

        doBFS();
        // System.out.println(Arrays.toString(answers));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("piepie.out")));
        Arrays.stream(answers).forEach(fout::println);
        fout.close();
    }

    void doBFS() {
        while (!bessieQ.isEmpty() || !elsieQ.isEmpty()) {
            Pie c;
            // Bessie's pies
            while (!bessieQ.isEmpty()) {
                c = bessieQ.poll();
                // Check which pies Elsie could've given Bessie to allow this one
                Pie okPie = elsiePies.floor(new Pie(c.b, 0, 987654321));
                while (okPie != null && okPie.b >= c.b - D) {
                    // Mark pie and add it
                    okPie.cost = c.cost + 1;
                    elsieQ.add(okPie);
                    elsiePies.remove(okPie);
                    okPie = elsiePies.floor(new Pie(c.b, 0, 987654321));
                }
            }
            // Elsie's pies
            while (!elsieQ.isEmpty()) {
                c = elsieQ.poll();
                // Check which pies Bessie could've given Elsie to allow this one
                Pie okPie = bessiePies.floor(new Pie(0, c.e, 987654321));
                while (okPie != null && okPie.e >= c.e - D) {
                    // Mark pie and add it
//                    System.out.println(okPie);
//                    System.out.println(c);
//                    System.out.println(Arrays.toString(answers));
                    okPie.cost = c.cost + 1;
                    answers[okPie.origI] = okPie.cost;
                    bessieQ.add(okPie);
                    bessiePies.remove(okPie);
                    okPie = bessiePies.floor(new Pie(0, c.e, 987654321));
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new piepie();
    }

    class Pie {
        int b, e, origI, cost;
        Pie(int b, int e, int origI) {
            this.b = b;
            this.e = e;
            this.origI = origI;
        }
        public String toString() {
            return String.format("(%d, %d, %d, %d)", b, e, origI, cost);
        }
    }
}