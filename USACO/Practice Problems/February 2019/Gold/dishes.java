/**
 * USACO 2019 February Contest, Gold
 * Problem 2. Dishwashing
 * 
 * Practice for USACO Gold. This one shouldn't be a problem.
 */

import java.util.*;
import java.io.*;

public class dishes {
	ArrayList<Deque<Integer>> stacks;
	int[] plates;
	int numPlates, currStack;
	final int INF = 999999999;
	boolean DEBUG = false;
	
	public dishes() throws IOException {
		getInput();
		int answer = solve();
		PrintWriter fout = new PrintWriter("dishes.out");
		if (DEBUG) System.out.println(answer);
		fout.println(answer);
		fout.close();
	}
	
	int solve() {
		stacks = new ArrayList<Deque<Integer>>();
		
		// Loop through each plate
		int maxCleanPlate = 0;
		int firstUnusedStack = 0;
		int currPlate;
		Deque<Integer> deque;
		for (int c = 0; c < numPlates; c++) {
			currPlate = plates[c];
			
			// If the current plate cannot be placed onto the clean stack, we're done
			if (maxCleanPlate > currPlate) {
				return c;
			}
			
			// Binary search for 1st stack with larger bottom value
			currStack = INF;
			binarySearch(currPlate, firstUnusedStack, stacks.size() - 1);
			if (DEBUG) System.out.println("Binary for " + currPlate + " gives " + currStack);
			
			if (currStack == INF) {
				// No bigger stack found; make a new one
				stacks.add(new LinkedList<Integer>());
				stacks.get(stacks.size() - 1).add(currPlate);
				if (DEBUG) System.out.println("New stack made");
			} else {
				// Check if this plate can be placed in this stack
				deque = stacks.get(currStack);
				if (deque.peekFirst() > currPlate) {
					// New plate can be put
					deque.addFirst(currPlate);
				} else {
					// Plates must be removed until you can place this plate
					firstUnusedStack = currStack;
					while (deque.peekFirst() < currPlate) {
						maxCleanPlate = Math.max(deque.pollFirst(), maxCleanPlate);
						if (deque.size() == 0) {
							// All the plates have been removed...?
							break;
						}
					}
					
					// Now place it
					deque.addFirst(currPlate);
					if (DEBUG) System.out.println("Plate put in stack " + currStack + " after removing to plate " + maxCleanPlate);
				}
			}
		}
		
		// All plates can be placed
		return numPlates;
	}
	
	void binarySearch(int value, int start, int end) {
		if (start > end) return;
		
		int middle = (start + end) / 2;
		if (value < stacks.get(middle).peekLast()) {
			currStack = Math.min(middle, currStack);
			binarySearch(value, start, middle - 1);
		} else {
			binarySearch(value, middle + 1, end);
		}
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("dishes.in"));
		numPlates = Integer.parseInt(fin.readLine());
		
		plates = new int[numPlates];
		for (int i = 0; i < numPlates; i++) {
			plates[i] = Integer.parseInt(fin.readLine());
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new dishes();
	}

}
