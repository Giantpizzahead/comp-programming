/**
 * USACO 2019 February Contest - Silver
 * Problem 2. Painting the Barn
 * 
 * This is for USACO prep / practice. I'm redoing this problem to practice the concept
 * of sweeping.
 * 
 */

import java.util.*;
import java.io.*;

public class paintbarn {
	Range[] ranges;
	int[] numRectsAtY, lastChanged;
	int numRects, targetNum, answer;
	int MAX_X = 1000, MAX_Y = 1000;
	boolean DEBUG = false;
	BufferedReader s;
	
	public paintbarn() throws IOException {
		getInput();
		if (DEBUG) System.out.println(Arrays.toString(ranges));
		doSweep();
		
		PrintWriter fout = new PrintWriter("paintbarn.out");
		fout.println(answer);
		fout.close();
		if (DEBUG) System.out.println("Answer: " + answer);
	}
	
	/**
	 * Sweeps through the list of ranges, counting the number of squares filled with targetNum coats of paint.
	 */
	public void doSweep() {
		numRectsAtY = new int[MAX_Y];
		lastChanged = new int[MAX_Y];
		
		int x, startY, endY, change;
		Type type;
		for (Range r : ranges) {
			x = r.x;
			startY = r.startY;
			endY = r.endY;
			type = r.type;
			
			// Start actual comparisons
			if (type == Type.START) {
				change = 1;
			} else {
				change = -1;
			}
			
			// Add to answer if needed, then update rect counts within the given Y range
			for (int y = startY; y < endY; y++) {
				// Add to answer
				if (numRectsAtY[y] == targetNum) {
					answer += x - lastChanged[y];
					if (DEBUG) System.out.println("Added " + (x - lastChanged[y]) + " to answer at " + x + ", " + y);
				}
				
				// Update values
				numRectsAtY[y] += change;
				lastChanged[y] = x;
			}
		}
		
		// Do a final check of the array
		for (int y = 0; y < MAX_Y; y++) {
			// Add to answer
			if (numRectsAtY[y] == targetNum) {
				answer += MAX_X - lastChanged[y];
				if (DEBUG) System.out.println("Added " + (MAX_X - lastChanged[y]) + " to answer at final check");
			}
		}
		
		if (DEBUG) System.out.println("All zero: " + Arrays.stream(numRectsAtY).allMatch(n -> n == 0));
	}
	
	public void getInput() throws IOException {
		s = new BufferedReader(new FileReader("paintbarn.in"));
		int[] line = getLine();
		numRects = line[0];
		targetNum = line[1];
		
		// Turn each rectangle into two ranges
		ranges = new Range[numRects * 2];
		int x1, y1, x2, y2;
		
		for (int i = 0; i < numRects; i++) {
			line = getLine();
			x1 = line[0];
			y1 = line[1];
			x2 = line[2];
			y2 = line[3];
			
			// Convert rectangle to ranges
			ranges[i*2] = new Range(x1, y1, y2, Type.START);
			ranges[i*2+1] = new Range(x2, y1, y2, Type.END);
		}
		
		// Sort the ranges array, smallest x first, then end range first (arbitrary y coordinate)
		Arrays.sort(ranges, new Comparator<Range>() {

			@Override
			public int compare(Range r1, Range r2) {
				if (r1.x < r2.x) {
					return -1;
				} else if (r1.x > r2.x) {
					return 1;
				} else if (r1.type == Type.END && r2.type == Type.START) {
					return -1;
				} else if (r1.type == Type.START && r2.type == Type.END) {
					return 1;
				} else {
					return 0;
				}
			}
			
		});
	}
	
	int[] getLine() throws IOException {
		String[] line = s.readLine().split(" ");
		return Arrays.stream(line).mapToInt(x -> Integer.parseInt(x)).toArray();
	}

	public static void main(String[] args) throws IOException {
		new paintbarn();
	}
	
}

enum Type {
	START,
	END;
}

class Range {
	int x, startY, endY;
	Type type;
	
	Range(int x, int startY, int endY, Type type) {
		this.x = x;
		this.startY = startY;
		this.endY = endY;
		this.type = type;
	}
	
	@Override
	public String toString() {
		return "Range[" + x + " " + startY + " " + endY + " " + type + "]";
	}
}