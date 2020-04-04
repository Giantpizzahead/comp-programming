/**
 * 
 * Retrying this problem, thinking of the mountains like line segments instead.
 * Each mountain peak can be represented by a line segment from x-y to x+y.
 * Find the # of segments that are not completely enclosed by another line
 * 
 * @author Kyle Fu
 * 
 **/

import java.util.*;
import java.io.*;

public class mountainsSegments {
	
	public static Segment[] segments;
	public static int numSegments;
	public static int INF = 999999999;

	public static void main(String[] args) throws IOException {
		getInput();
		int answer = sweepSegments();
		PrintWriter fout = new PrintWriter("mountains.out");
		fout.println(answer);
		fout.close();
	}
	
	public static int sweepSegments() {
		int numVisible = 0;
		int maxEndpoint = -INF;

		// Iterate through all segments
		for (Segment seg : segments) {
			if (seg.e > maxEndpoint) {
				// Current segment is not fully enclosed
				numVisible++;
				maxEndpoint = seg.e;
			}
		}
		
		return numVisible;
	}
	
	public static void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("mountains.in"));
		numSegments = Integer.parseInt(fin.readLine());
		
		// Parse all segments
		segments = new Segment[numSegments];
		String[] line;
		int x, y;
		for (int i = 0; i < numSegments; i++) {
			line = fin.readLine().split(" ");
			x = Integer.parseInt(line[0]);
			y = Integer.parseInt(line[1]);
			segments[i] = new Segment(x - y, x + y);
		}
		
		// Sort segments array
		Arrays.sort(segments, new SegmentComp());
		
		fin.close();
	}
	
	static class Segment {
		int s, e;
		public Segment(int s, int e) {
			this.s = s;
			this.e = e;
		}
	}
	
	static class SegmentComp implements Comparator<Segment> {
		
		@Override
		public int compare(Segment s1, Segment s2) {
			// Sort segments by start point, breaking ties by furthest end point
			if (s1.s > s2.s) {
				return 1;
			} else if (s1.s < s2.s) {
				return -1;
			} else if (s1.e < s2.e) {
				return 1;
			} else if (s1.e > s2.e) {
				return -1;
			} else {
				return 0;
			}
		}
		
	}

}
