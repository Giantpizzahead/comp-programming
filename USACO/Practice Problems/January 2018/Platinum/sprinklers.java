import java.util.*;
import java.io.*;

public class sprinklers {
    int N;
    int[] fertYs, waterYs;
    final long MOD = 1000000007;

    sprinklers() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sprinklers.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        fertYs = new int[N];
        waterYs = new int[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            fertYs[x] = y;
            waterYs[x] = y;
        }
        fin.close();

        // Generate correct ys by sweeping
        for (int i = 1; i < N; i++) {
            waterYs[i] = Math.min(waterYs[i-1], waterYs[i]);
        }
        for (int i = N - 2; i >= 0; i--) {
            fertYs[i] = Math.max(fertYs[i+1], fertYs[i]);
        }
//        System.out.println(Arrays.toString(waterYs));
//        System.out.println(Arrays.toString(fertYs));

        // Find rectangles
        long answer = findNumRects();
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sprinklers.out")));
        fout.println(answer);
        fout.close();
    }

    long findNumRects() {
        BIT pastRectBIT = new BIT(N);
        int currFertY = fertYs[1];
        int currWaterY = waterYs[0];
        long activeRectSum = 0;
        long answer = 0;

        // Offset fertYs by 1
        for (int i = 0; i < N - 1; i++) {
            while (currFertY > fertYs[i+1]) {
                // Remove past rectangles that can no longer be extended
                activeRectSum -= pastRectBIT.queryRects(currFertY - 1)
                                 + pastRectBIT.queryCount(currFertY - 1) * (currFertY - 1);
                activeRectSum %= MOD;
                if (activeRectSum < 0) activeRectSum += MOD;
                currFertY--;
            }
            currWaterY = waterYs[i];

            if (currWaterY >= currFertY) continue;  // No rectangles can be made here

            // Update # of active rectangles (start rectangle at this x)
            activeRectSum += (long) (currFertY - currWaterY) * (currFertY - currWaterY + 1) / 2;
            activeRectSum %= MOD;

            // Add # of rectangles started at this x, relative to y coordinate to allow range addition
            pastRectBIT.update(currWaterY, currFertY - 1, 1 - currWaterY);

            answer = (answer + activeRectSum) % MOD;
//            System.out.println("At x=" + i);
//            System.out.println("# active: " + activeRectSum);
//            System.out.println("Answer: " + answer);
        }

        return answer;
    }

    public static void main(String[] args) throws IOException {
        new sprinklers();
    }

    class BIT {
        int size;
        long[] numRects, count;
        BIT(int size) {
            this.size = size;
            numRects = new long[size + 1];
            count = new long[size + 1];
        }

        void update(int a, int b, int v) {
            a++;
            b++;
            update(a, v);
            update(b+1, -v);
        }

        void update(int i, int v) {
            while (i <= size) {
                numRects[i] = (numRects[i] + v) % MOD;
                count[i]++;
                i += Integer.lowestOneBit(i);
            }
        }

        long queryRects(int i) {
            i++;
            long result = 0;
            while (i > 0) {
                result += numRects[i];
                i -= Integer.lowestOneBit(i);
            }
            return result % MOD;
        }

        long queryCount(int i) {
            i++;
            int result = 0;
            while (i > 0) {
                result += count[i];
                i -= Integer.lowestOneBit(i);
            }
            return result;
        }
    }
}
