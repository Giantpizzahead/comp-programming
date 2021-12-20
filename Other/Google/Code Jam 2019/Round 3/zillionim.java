import java.util.*;
import java.io.*;

public class zillionim {
    final long RANGE_SIZE = 10_000_000_000L;
    ArrayList<Range> ranges;

    zillionim(BufferedReader in, int tn) throws IOException {
        ranges = new ArrayList<>();
        ranges.add(new Range(1, 1_000_000_000_000L));
        long P;
        boolean switched = false;
        while (true) {
            P = Long.parseLong(in.readLine());
            if (P < 0) return;
            // Handle AI's split point
            for (int i = 0; i < ranges.size(); i++) {
                if (ranges.get(i).l <= P && ranges.get(i).r >= P) {
                    // AI split this range
                    splitRange(i, P, false);
                    break;
                }
            }
            // System.err.println(ranges);
            // Create as many 2s as possible
            boolean split = false;
            ArrayList<Integer> lessRanges = new ArrayList<>(2), twoRanges = new ArrayList<>(2);
            for (int i = 0; i < ranges.size(); i++) {
                Range currRange = ranges.get(i);
                if (currRange.rangeSize() >= RANGE_SIZE * 3) {
                    // Split range to make a 2
                    splitRange(i, currRange.l + RANGE_SIZE * 2, true);
                    split = true;
                    break;
                } else if (currRange.rangeSize() > RANGE_SIZE * 2) {
                    // This range is sort of useless; destroy it
                    splitRange(i, currRange.l + RANGE_SIZE - 2, true);
                    split = true;
                    break;
                } else if (currRange.rangeSize() == RANGE_SIZE * 2) twoRanges.add(i);
                else lessRanges.add(i);
            }
            if (!split) {
//                if (!switched) {
//                    switched = true;
//                    System.err.println("Switched: " + lessRanges.size() + " " + twoRanges.size());
//                } else {
//                    System.err.println("on: " + lessRanges.size() + " " + twoRanges.size());
//                }
                // System.err.println("split");
                // Down to only small ranges (<= 2)
                if (twoRanges.size() == 1) {
                    // Play based on current less parity
                    if (lessRanges.size() % 2 == 0) {
                        // Fill entire range
                        splitRange(twoRanges.get(0), ranges.get(twoRanges.get(0)).l + 10000000, true);
                    } else {
                        // Fill one portion
                        splitRange(twoRanges.get(0), ranges.get(twoRanges.get(0)).l, true);
                    }
                } else if (twoRanges.size() == 2 && lessRanges.size() == 0) {
                    // Fill one portion
                    splitRange(twoRanges.get(0), ranges.get(twoRanges.get(0)).l, true);
                } else {
                    // Play some valid range
                    if (lessRanges.size() != 0) splitRange(lessRanges.get(0), ranges.get(lessRanges.get(0)).l, true);
                    else splitRange(0, ranges.get(0).l, true);
                }
            }
            // System.err.println(ranges);
        }
    }

    void splitRange(int i, long at, boolean print) {
        if (print) {
            System.out.println(at);
            // System.err.println("splitting " + at);
        }
        Range currRange = ranges.get(i);
        ranges.remove(i);
        Range leftRange = new Range(currRange.l, at - 1);
        Range rightRange = new Range(at + RANGE_SIZE, currRange.r);
        if (rightRange.rangeSize() >= RANGE_SIZE) ranges.add(i, rightRange);
        if (leftRange.rangeSize() >= RANGE_SIZE) ranges.add(i, leftRange);
    }

    class Range {
        long l, r;
        Range(long l, long r) {
            this.l = l;
            this.r = r;
        }
        long rangeSize() {
            return r - l + 1;
        }
        public String toString() {
            return "(" + l + ", " + r + ")";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        int T = Integer.parseInt(st.nextToken());
        for (int i = 1; i <= T; i++) new zillionim(in, i);
        in.close();
    }
}
