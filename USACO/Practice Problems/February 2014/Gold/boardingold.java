/**
 * USACO 2014 February Contest (Gold -> Platinum)
 * Problem 3. Airplane Boarding
 * 
 * I've had a longgggg time to think about this one. Now I'm ready to solve it.
 * Let's go! :)
 */

import java.util.*;
import java.io.*;

public class boarding {
	int[] targetSeats, waitTime;
	int numCows;
	boolean DEBUG = false;
	
	boarding() throws IOException {
		getInput();
		int answer = solve();
		
		if (DEBUG) {
			System.out.println(Arrays.toString(targetSeats));
			System.out.println(Arrays.toString(waitTime));
			System.out.println(answer);
		}
		PrintWriter fout = new PrintWriter("boarding.out");
		fout.println(answer);
		fout.close();
	}
	
	int solve() {
		int answer = 0;
		MaxFinder maxFinder = new MaxFinder(numCows);
		
		// Iterate through all the cows, and calculate the time it takes for each to sit
		int timeTaken;
		for (int i = 0; i < numCows; i++) {
			timeTaken = Math.max(maxFinder.query(targetSeats[i]) + targetSeats[i], 1 + i + targetSeats[i]) + waitTime[i];
			if (DEBUG) System.out.println("Time taken for cow " + i + ": " + timeTaken);
			answer = Math.max(timeTaken, answer);
			
			// Move all the passed by ones to the left one seat
			for (int j = 0; j < targetSeats[i]; j++) {
				maxFinder.insert(j, maxFinder.get(j+1));
			}
			
			// Insert the time taken into maxFinder to simulate a line block at that location
			maxFinder.insert(targetSeats[i], timeTaken + 1 - targetSeats[i]);
		}
		
		return answer;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("boarding.in"));
		numCows = Integer.parseInt(fin.readLine());
		targetSeats = new int[numCows];
		waitTime = new int[numCows];
		
		// Parse all cows in reverse order
		String[] line;
		for (int i = numCows - 1; i >= 0; i--) {
			line = fin.readLine().split(" ");
			targetSeats[i] = Integer.parseInt(line[0]) - 1;
			waitTime[i] = Integer.parseInt(line[1]);
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new boarding();
	}

}

class MaxFinder {
	int[] maxes, minI, maxI;
	int numNums, numNodes;
	boolean DEBUG = false;
	
	public MaxFinder(int numNums) {
		// Change # of nums into a power of 2 for easier implementation
		int power = 0;
		while (numNums != 1) {
			numNums = (numNums + 1) / 2;
			power++;
		}
		
		this.numNums = (int) Math.pow(2, power);
		numNodes = this.numNums * 2 - 1;
		if (DEBUG) System.out.println("Actual nums: " + this.numNums);
		
		// Initialize the binary tree
		maxes = new int[numNodes];
		minI = new int[numNodes];
		maxI = new int[numNodes];
		
		initMinMaxes();
	}
	
	/**
	 * Sets up the minI and maxI arrays with the right values.
	 * minI has the minimum index of the current node's max (inclusive).
	 * maxI has the maximum index of the current node's max (exclusive).
	 */
	void initMinMaxes() {
		int currAdd = numNums;
		int currNum = 0;
		
		for (int i = 0; i < numNodes; i++) {
			minI[i] = currNum;
			currNum += currAdd;
			maxI[i] = currNum;
			
			if (currNum == numNums) {
				currNum = 0;
				currAdd /= 2;
			}
		}
		
		if (DEBUG) {
			System.out.println("Index arrays:");
			System.out.println(Arrays.toString(minI));
			System.out.println(Arrays.toString(maxI));
		}
	}
	
	void insert(int index, int num) {
		if (DEBUG) System.out.println("Inserted " + num + " at index " + index);
		int node = 0;
		int cutoff;
		while (true) {
			maxes[node] = Math.max(num, maxes[node]);
			
			// Stop if at end node
			if (maxI[node] - minI[node] == 1) break;
			
			// Figure out whether the current index is in the left or right node
			cutoff = (minI[node] + maxI[node]) / 2;
			if (index < cutoff) {
				// Left node
				node = node * 2 + 1;
			} else {
				// Right node
				node = node * 2 + 2;
			}
		}
	}
	
	int get(int index) {
		return maxes[numNodes - numNums + index];
	}
	
	int query(int end) {
		int node = 0;
		int answer = 0;
		int cutoff;
		while (true) {
			// Check if the current node encloses the entire checked area
			if (maxI[node] - 1 == end) {
				// Return the answer
				return Math.max(maxes[node], answer);
			} else {
				// Figure out whether to check the left or right node
				cutoff = (minI[node] + maxI[node]) / 2;
				if (end < cutoff) {
					// Left node
					node = node * 2 + 1;
				} else {
					// Right node, but add the max of the left node first
					answer = Math.max(maxes[node * 2 + 1], answer);
					node = node * 2 + 2;
				}
			}
		}
	}
	
}