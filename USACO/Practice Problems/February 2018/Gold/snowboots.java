/*
Solution: Put the tiles into a disjoint set in order of decreasing snow height. When adding a new tile,
record the size of the new set / min value in that range. Sort these records in decreasing min value
order.

Then, sort boots by max allowed snow (decreasing order). Iterate through disjoint set records, with
pointer to current boot. While current boot's snow allowed >= max val in current reocrd, mark this boot
as 1 and move to next snow boot. After moving, while current boot's step size <= size of set, mark with
0 and move to next snow boot.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class snowboots {
    int N, B;
    Tile[] tiles;
    Boot[] boots;
    ArrayList<Record> records;
    final int INF = 1000000007;

    snowboots() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("snowboots.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        tiles = new Tile[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) {
            tiles[i] = new Tile(Integer.parseInt(st.nextToken()), i);
        }
        boots = new Boot[B];
        int maxSnow, stepSize;
        for (int i = 0; i < B; i++) {
            st = new StringTokenizer(fin.readLine());
            maxSnow = Integer.parseInt(st.nextToken());
            stepSize = Integer.parseInt(st.nextToken());
            boots[i] = new Boot(maxSnow, stepSize, i);
        }
        fin.close();
        
        // Part 1: Generate records from disjoint set
        genRecords();

        // System.out.println(records);

        // Part 2: Find out which boots work
        testBoots();

        // Finally, print results in the right order
        boolean[] results = new boolean[B];
        for (Boot boot : boots) {
            results[boot.origI] = boot.canUse;
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("snowboots.out")));
        for (boolean b : results) {
            fout.println(b ? 1 : 0);
        }
        fout.close();
    }

    void testBoots() {
        Arrays.sort(boots, new Comparator<Boot>() {
            @Override
            public int compare(Boot a, Boot b) {
                if (a.step == b.step) return b.d - a.d;
                else return a.step - b.step;
            }
        });
        // System.out.println(Arrays.toString(boots));
        int bootI = 0;
        for (Record r : records) {
            // System.out.println("Record: " + r);
            while (boots[bootI].step <= r.s) {
                if (boots[bootI].d >= r.d) {
                    boots[bootI].canUse = true;
                }
                bootI++;
                if (bootI == B) return;
            }
        }
    }
    
    void genRecords() {
        DisjointSet ds = new DisjointSet(N);
        Arrays.sort(tiles, Comparator.comparingInt(x -> -x.d));
        // To avoid multiple records of same size
        boolean[] sizeRecorded = new boolean[N + 1];
        records = new ArrayList<>();

        Tile c;
        int size;
        for (int i = 0; i < N; i++) {
            c = tiles[i];
            ds.active[c.i] = true;

            if (c.i != 0 && ds.active[c.i - 1]) {
                /*
                // Add record joining with only left set
                size = ds.setSize(c.i - 1) + 1;
                if (!sizeRecorded[size]) {
                    sizeRecorded[size] = true;
                    records.add(new Record(c.d, size));
                }
                 */
                ds.merge(c.i, c.i - 1);
            }

            if (c.i != N-1 && ds.active[c.i + 1]) {
                /*
                // Add record joining with only right set
                size = ds.setSize(c.i + 1) + 1;
                if (!sizeRecorded[size]) {
                    sizeRecorded[size] = true;
                    records.add(new Record(c.d, size));
                }
                 */
                ds.merge(c.i, c.i + 1);
            }

            // Add a new record (if needed)
            size = ds.setSize(c.i);
            if (!sizeRecorded[size]) {
                sizeRecorded[size] = true;
                records.add(new Record(c.d, size));
            }
        }

        records.sort(new Comparator<Record>() {
            @Override
            public int compare(Record a, Record b) {
                if (a.d == b.d) return b.s - a.s;
                else return b.d - a.d;
            }
        });
    }

    public static void main(String[] args) throws IOException {
        new snowboots();
    }

    class DisjointSet {
        int size;
        int[] arr, minInSet;
        boolean[] active;

        DisjointSet(int size) {
            this.size = size;
            arr = new int[size];
            minInSet = new int[size];
            active = new boolean[size];
            for (int i = 0; i < size; i++) {
                arr[i] = -1;
                minInSet[i] = tiles[i].d;
            }
        }

        boolean merge(int a, int b) {
            active[a] = true;
            active[b] = true;
            int setA = query(a);
            int setB = query(b);
            if (setA == setB) return false;  // Already in same set

            // Merge into set with more values
            if (setSize(setA) > setSize(setB)) {
                arr[setA] += arr[setB];
                arr[setB] = setA;
                minInSet[setA] = Math.min(minInSet[setA], minInSet[setB]);
            } else {
                arr[setB] += arr[setA];
                arr[setA] = setB;
                minInSet[setB] = Math.min(minInSet[setA], minInSet[setB]);
            }
            return true;
        }

        int query(int index) {
            if (arr[index] < 0) return index;
            else {
                int result = query(arr[index]);
                arr[index] = result;
                return result;
            }
        }

        int setSize(int index) {
            int set = query(index);
            return -arr[set];
        }

        int setMin(int index) {
            int set = query(index);
            return minInSet[set];
        }

        @Override
        public String toString() {
            return "DS" + Arrays.toString(arr);
        }
    }
}

class Boot {
    int d, step, origI;
    boolean canUse;
    Boot(int d, int step, int origI) {
        this.d = d;
        this.step = step;
        this.origI = origI;
    }

    @Override
    public String toString() {
        return "(" + d + ", " + step + ")";
    }
}

class Record {
    int d, s;
    Record(int d, int s) {
        this.d = d;
        this.s = s;
    }

    @Override
    public String toString() {
        return "(" + d + ", " + s + ")";
    }
}

class Tile {
    int d, i;
    Tile(int d, int i) {
        this.d = d;
        this.i = i;
    }
}