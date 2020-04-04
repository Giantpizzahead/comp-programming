/*
Solution: The costs to use a slingshot can be modeled by an absolute value
equation if you constrain where the start point of the slingshot is relative
to the manure location. First, split the problem up into transporting manure
right with right slingshots, and vice versa (just flip everything when
solving again). If you sort the manure in increasing order of start location,
you can create an absolute value equation holder for slingshots that start
behind the manure, and sling the manure closer to the goal. A similar idea
can be applied to the equations for slingshots in front of the manure. Just
take the minimum of these results (plus raw tractor distance) to get the
answer.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class slingshot {
    int N, M;
    long[] answers;
    ArrayList<Slingshot> slingshots, oppDirSlingshots;
    ArrayList<Manure> manure, oppDirManure;
    final long INF = 200000000000L;

    slingshot() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("slingshot.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        slingshots = new ArrayList<>();
        oppDirSlingshots = new ArrayList<>();
        manure = new ArrayList<>();
        oppDirManure = new ArrayList<>();
        answers = new long[M];
        Arrays.fill(answers, INF);
        int a, b, c;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            if (a < b) slingshots.add(new Slingshot(a, b, c));
            else if (a > b) oppDirSlingshots.add(new Slingshot(a, b, c));
        }
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            if (a == b) answers[i] = 0;
            else if (a < b) manure.add(new Manure(a, b, i));
            else oppDirManure.add(new Manure(a, b, i));
        }
        fin.close();

//        AbsHolder abs = new AbsHolder();
//        abs.add(new Slingshot(1, 2, 1));
//        abs.add(new Slingshot(1, 6, 4));
//        abs.add(new Slingshot(1, 10, 2));
//        abs.add(new Slingshot(1, 14, 7));
//        abs.add(new Slingshot(1, 18, 5));
//        for (int i = 0; i <= 20; i++) {
//            System.out.println(i + " -> " + abs.query(i));
//        }

        // Sort everything and run the algorithm
        slingshots.sort(Comparator.comparingInt(x -> x.x));
        manure.sort(Comparator.comparingInt(x -> x.a));
        findAnswers();

        // Now replace everything with its opposite and run the algorithm again
        slingshots.clear();
        manure.clear();
        for (Slingshot s : oppDirSlingshots) {
            int temp = s.x;
            s.x = s.y;
            s.y = temp;
            slingshots.add(s);
        }
        for (Manure m : oppDirManure) {
            int temp = m.a;
            m.a = m.b;
            m.b = temp;
            manure.add(m);
        }
        slingshots.sort(Comparator.comparingInt(x -> x.x));
        manure.sort(Comparator.comparingInt(x -> x.a));
        findAnswers();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("slingshot.out")));
        Arrays.stream(answers).forEach(fout::println);
        fout.close();
    }

    void findAnswers() {
        // First, find the distance if you use a slingshot behind you
        AbsHolder abs = new AbsHolder();
        int cSlingshot = 0;
        for (Manure m : manure) {
            while (cSlingshot < slingshots.size() && m.a >= slingshots.get(cSlingshot).x) {
                // System.out.println("Adding " + slingshots.get(cSlingshot));
                abs.add(slingshots.get(cSlingshot), -slingshots.get(cSlingshot).x);
                cSlingshot++;
            }
            answers[m.origI] = Math.min(abs.query(m.b) + m.a, answers[m.origI]);
            // System.out.println(answers[m.origI]);
        }

        // Next, find the distance if you use a slingshot in front of you
        abs.equations.clear();
        cSlingshot = slingshots.size() - 1;
        for (int i = manure.size() - 1; i >= 0; i--) {
            Manure m = manure.get(i);
            while (cSlingshot >= 0 && m.a <= slingshots.get(cSlingshot).x) {
                abs.add(slingshots.get(cSlingshot), slingshots.get(cSlingshot).x);
                cSlingshot--;
            }
            answers[m.origI] = Math.min(abs.query(m.b) - m.a, answers[m.origI]);
        }

        // Finally, find the raw tractor distance
        for (Manure m : manure) answers[m.origI] = Math.min(m.b - m.a, answers[m.origI]);
    }

    public static void main(String[] args) throws IOException {
        new slingshot();
    }

    class AbsHolder {
        TreeSet<Equation> equations = new TreeSet<>(Comparator.comparingLong(e -> e.x));

        void add(Slingshot s, int delta) {
            Equation e = new Equation(s.y, s.t + delta);
            // Remove any outdated equations on the left
            Equation l = equations.floor(e);
            while (l != null) {
                long overtaken;
                if (l.x < e.x) overtaken = l.overtaken(e);
                else overtaken = e.overtaken(l);
                if (overtaken == 0) {
                    // New equation is always better than this one; delete it
                    equations.remove(l);
                } else if (overtaken == INF) {
                    // New equation is always worse; don't add it
                    return;
                } else {
                    // Found overtake point, no need to remove anymore
                    break;
                }
                l = equations.floor(e);
            }
            // Remove any outdated equations on the right
            Equation r = equations.ceiling(e);
            while (r != null) {
                long overtaken;
                if (r.x < e.x) overtaken = r.overtaken(e);
                else overtaken = e.overtaken(r);
                if (overtaken == 0) {
                    // Right equation is always better than this one; stop adding it
                    return;
                } else if (overtaken == INF) {
                    // New equation is always better; remove old one
                    equations.remove(r);
                } else {
                    // Found overtake point, no need to remove anymore
                    break;
                }
                r = equations.ceiling(e);
            }

            equations.add(e);
            // System.out.println(equations);
        }

        // Returns the minimum value of all the absolute value equations at x.
        long query(int x) {
            Equation e1 = equations.floor(new Equation(x));
            Equation e2 = equations.ceiling(new Equation(x));
            if (e1 == null && e2 == null) return INF;
            else if (e1 == null) return e2.eval(x);
            else if (e2 == null) return e1.eval(x);
            else return Math.min(e1.eval(x), e2.eval(x));
        }
    }

    class Equation {
        // Vertex coordinates
        long x, y, overtakePoint;
        Equation(long x, long y) {
            this.x = x;
            this.y = y;
            overtakePoint = x;
        }

        Equation(long op) {
            x = op;
            overtakePoint = op;
        }

        long eval(long x) {
            return y + Math.abs(x - this.x);
        }

        // Returns the time that this equation is overtaken by the other one as the
        // equation with the minimum value (equal counts too).
        // Returns INF if this equation is never overtaken by the other one,
        // or 0 if the other equation is always better. If the 2 equations are the same,
        // this will return 0.
        // The other equation's x coordinate must be >= this one's x coord
        // for this to work!!!
        long overtaken(Equation other) {
            long low = 0, high = INF;
            while (low < high) {
                long mid = (low + high) / 2;
                if (eval(mid) < other.eval(mid)) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
            return low;
        }

        @Override
        public String toString() {
            return "(" + x + ", " + y + ", " + overtakePoint + ")";
        }
    }

    class Slingshot {
        int x, y, t;
        Slingshot(int x, int y, int t) {
            this.x = x;
            this.y = y;
            this.t = t;
        }
        @Override
        public String toString() {
            return "(" + x + ", " + y + ", " + t + ")";
        }
    }

    class Manure {
        int a, b, origI;
        Manure(int a, int b, int origI) {
            this.a = a;
            this.b = b;
            this.origI = origI;
        }
        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}