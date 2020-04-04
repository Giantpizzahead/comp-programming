/*
ID: sunnyky1
LANG: JAVA
TASK: milk

Solution: Greedily choose the farmer offering the milk at the lowest unit cost. Buy as much
as possible from that farmer, then move on to the next until you've bought enough milk.
Complexity: O(M*log(M)) for sorting
*/

import java.util.*;
import java.io.*;

public class milk {
    static int target, numFarmers;
    static Farmer[] farmers;

    public static void main(String[] args) throws IOException {
        // Input parsing
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        target = Integer.parseInt(st.nextToken());
        numFarmers = Integer.parseInt(st.nextToken());
        farmers = new Farmer[numFarmers];

        // Parse all the farmers
        int p, a;
        for (int i = 0; i < numFarmers; i++) {
            st = new StringTokenizer(fin.readLine());
            p = Integer.parseInt(st.nextToken());
            a = Integer.parseInt(st.nextToken());
            farmers[i] = new Farmer(p, a);
        }

        fin.close();

        // Sort farmers by lowest unit cost
        Arrays.sort(farmers, Comparator.comparingInt(f -> f.p));

        // Run greedy algorithm
        int price = 0;
        int unitsBought;
        for (int i = 0; i < numFarmers; i++) {
            if (target == 0) break;
            unitsBought = Math.min(farmers[i].a, target);
            price += farmers[i].p * unitsBought;
            target -= unitsBought;
        }

        // Output answer
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk.out")));
        fout.println(price);
        fout.close();
    }

    static class Farmer {
        int p, a;
        Farmer(int p, int a) {
            this.p = p;
            this.a = a;
        }
    }
}
