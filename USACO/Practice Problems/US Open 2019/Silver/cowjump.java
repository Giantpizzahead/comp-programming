/**
 * USACO 2019 US Open Contest - Silver
 * Problem 2. Cow Steeplechase II
 * 
 * This is a redo of this problem, to practice for USACO.
 */

import java.util.*;
import java.io.*;

public class cowjump {
	Segment[] segments;
	Point[] points;
	int numSegments;

	cowjump() throws IOException {
		getInput();
		//System.out.println(Arrays.toString(points));
		/*
		for (int i = 0; i < numSegments; i++) {
			for (int j = i+1; j < numSegments; j++) {
				System.out.println(i + " " + j + " " + segments[i].checkIntersect(segments[j]));
			}
		}
		*/
		
		
		int answer = doSweep() + 1;
		
		System.out.println(answer);
		PrintWriter fout = new PrintWriter("cowjump.out");
		fout.println(answer);
		fout.close();
	}
	
	int doSweep() {
		ArrayList<Integer> currSegs = new ArrayList<Integer>();
		boolean intersect;
		int intersected1 = -1, intersected2 = -1, iToRemove = -1, s;
		
		for (Point point : points) {
			if (point.t == 0) {
				// Start point; add the segment
				currSegs.add(point.id);
			} else {
				// End point; check for any intersections, then remove the segment
				for (int i = 0; i < currSegs.size(); i++) {
					s = currSegs.get(i);
					if (point.id != s) {
						intersect = segments[point.id].checkIntersect(segments[s]);
						if (intersect) {
							// These segments intersect; record it, or return the answer
							if (intersected1 == point.id || intersected1 == s) {
								// This segment has intersected more than 1 segment; it must be removed
								return intersected1;
							} else if (intersected2 == point.id || intersected2 == s) {
								// Same as above
								return intersected2;
							} else {
								// Add new segments to check
								intersected1 = point.id;
								intersected2 = s;
							}
						}
					} else {
						// Remove this segment
						iToRemove = i;
					}
				};
				
				currSegs.remove(iToRemove);
			}
		}
		
		// Return least found segment
		return Math.min(intersected1, intersected2);
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("cowjump.in"));
		numSegments = Integer.parseInt(fin.readLine());
		
		// Parse all the segments
		segments = new Segment[numSegments];
		points = new Point[numSegments*2];
		String[] line;
		int x1, y1, x2, y2;
		for (int i = 0; i < numSegments; i++) {
			line = fin.readLine().split(" ");
			x1 = Integer.parseInt(line[0]);
			y1 = Integer.parseInt(line[1]);
			x2 = Integer.parseInt(line[2]);
			y2 = Integer.parseInt(line[3]);
			
			segments[i] = new Segment(x1, y1, x2, y2);
			points[i*2] = new Point((int) segments[i].sx, (int) segments[i].sy, i, 0);
			points[i*2+1] = new Point((int) segments[i].ex, (int) segments[i].ey, i, 1);
		}
		
		fin.close();
		
		// Sort points by x coordinate, with start points first
		Arrays.sort(points, (Comparator<Point>) (a, b) -> {
			if (a.x < b.x) {
				return -1;
			} else if (b.x < a.x) {
				return 1;
			} else if (a.t < b.t) {
				return -1;
			} else if (b.t < a.t) {
				return 1;
			} else {
				return 0;
			}
		});
	}
	
	class Segment {
		long sx, sy, ex, ey;
		double slope;
		boolean isVertical;
		
		public Segment(int x1, int y1, int x2, int y2) {
			// Figure out which point is the start and end point
			if (x1 < x2) {
				// Point 1 is start
				sx = x1;
				sy = y1;
				ex = x2;
				ey = y2;
				slope = (double) (ey - sy) / (double) (ex - sx);
				isVertical = false;
			} else if (x2 < x1) {
				// Point 2 is start
				sx = x2;
				sy = y2;
				ex = x1;
				ey = y1;
				slope = (double) (ey - sy) / (double) (ex - sx);
				isVertical = false;
			} else {
				// This is a vertical segment
				sx = x1;
				sy = Math.min(y1, y2);
				ex = x2;
				ey = Math.max(y1, y2);
				slope = 0;
				isVertical = true;
			}
		}
		
		/**
		 * Returns whether or not this segment intersects with the other one.
		 */
		boolean checkIntersect(Segment o) {
			// Check if they occupy the same x values
			if (ex < o.sx || o.ex < sx) {
				// No need to check; they don't occupy the same x bounds
				return false;
			}
			
			// Figure out the x values to check in between
			long minX = Math.max(sx, o.sx);
			long maxX = Math.min(ex, o.ex);
			
			// Find out what y value each segment is at both minX and maxX
			double minY1 = sy + slope * (minX - sx);
			double maxY1 = sy + slope * (maxX - sx);
			double minY2 = o.sy + o.slope * (minX - o.sx);
			double maxY2 = o.sy + o.slope * (maxX - o.sx);
			
			if (isVertical && o.isVertical) {
				// Special case: Check if the segments are on the same x coordinate and at
				// least one of the other's points is in between or on this segment's points
				return sx == o.sx && ((o.sy >= sy && o.sy <= ey) || (o.ey >= sy && o.ey <= ey));
			} else if (isVertical) {
				// Special case: Check if the non-vertical segment's point is within this segment's y values
				return minY2 >= sy && minY2 <= ey;
			} else if (o.isVertical) {
				// Do the same as above, but with the segments switched
				return minY1 >= o.sy && minY1 <= o.ey;
			} else {
				// Check if the points cross over each other; if they do, the segments must intersect
				return ((minY1 < minY2) != (maxY1 < maxY2) || minY1 == minY2 || maxY1 == maxY2);
			}
		}
	}
	
	class Point {
		int x, y, id, t;
		
		public Point(int x, int y, int id, int t) {
			this.x = x;
			this.y = y;
			this.id = id;
			this.t = t;
		}
		
		@Override
		public String toString() {
			return "Point(" + x + ", " + y + ", " + id + ", " + t + ")";
		}
	}
	
	public static void main(String[] args) throws IOException {
		new cowjump();
	}

}