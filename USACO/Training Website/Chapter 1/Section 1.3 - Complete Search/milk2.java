/*
ID: sunnyky1
LANG: JAVA
TASK: milk2
*/

import java.util.*;
import java.io.*;

public class milk2 {
	static int numFarmers, numMilking, lastX, longestOn, longestIdle;
	static Point[] milkPoints;

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("milk2.in"));
		numFarmers = Integer.parseInt(fin.readLine());
		
		milkPoints = new Point[numFarmers * 2];
		StringTokenizer st;
		for (int i = 0; i < numFarmers; i++) {
			st = new StringTokenizer(fin.readLine());
			milkPoints[i*2] = new Point(Integer.parseInt(st.nextToken()), 0);
			milkPoints[i*2+1] = new Point(Integer.parseInt(st.nextToken()), 1);
		}
		
		// Sort the points by x coordinate, breaking ties by start point first
		Arrays.sort(milkPoints, new Comparator<Point>() {
			@Override
			public int compare(Point p1, Point p2) {
				if (p1.x < p2.x) return -1;
				else if (p2.x < p1.x) return 1;
				else if (p1.t < p2.t) return -1;
				else if (p2.t < p1.t) return 1;
				else return 0;
			}
		});
		
		fin.close();
		
		// Do a simple scan
		lastX = milkPoints[0].x;
		longestOn = 0;
		longestIdle = 0;
		numMilking = 0;
		for (Point p : milkPoints) {
			if (numMilking == 0) {
				longestIdle = Math.max(p.x - lastX, longestIdle);
				lastX = p.x;
			}
			
			if (p.t == 0) {
				numMilking++;
			} else {
				numMilking--;
				if (numMilking == 0) {
					longestOn = Math.max(p.x - lastX, longestOn);
					lastX = p.x;
				}
			}
		}
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
		fout.println(longestOn + " " + longestIdle);
		fout.close();
	}

}

class Point {
	int x, t;
	public Point(int x, int t) {
		this.x = x;
		this.t = t;
	}
}