/**
 * USACO 2019 US Open Contest, Silver
 * Problem 1. Left Out
 * 
 * This is a redo of this silver problem, but in Java / using a better,
 * faster method (I think).
 * 
 * Doing this because the Python solution timed out on ONE test case... :(
 *
 */

import java.io.*;

public class leftout {
	boolean[][] cows;
	int numCows, outX, outY;

	public leftout() throws IOException {
		getInput();
		
		/*
		// Randomize the input
		for (int n = 0; n < numCows; n++) {
			if (Math.random() > 0.5d) {
				flipRow(n);
			}
			if (Math.random() > 0.5d) {
				flipColumn(n);
			}
		}
		*/
		
		fixFirstRow();
		findOddCowOut();
		
		/*
		if (outX == -1) {
			System.out.println("-1");
		} else {
			System.out.println((outY + 1) + " " + (outX + 1));
		}
		*/
		
		PrintWriter fout = new PrintWriter("leftout.out");
		if (outX == -1) {
			fout.println("-1");
		} else {
			fout.println((outY + 1) + " " + (outX + 1));
		}
		
		fout.close();
	}
	
	void findOddCowOut() {
		boolean outFound = false;
		outX = -1;
		outY = -1;
		int numFalse, numTrue;
		int firstFalse, firstTrue;
		
		for (int y = 1; y < numCows; y++) {
			numFalse = 0;
			numTrue = 0;
			firstFalse = -1;
			firstTrue = -1;
			for (int x = 0; x < numCows; x++) {
				if (cows[y][x]) {
					numTrue++;
					if (firstTrue == -1) {
						firstTrue = x;
					}
				} else {
					numFalse++;
					if (firstFalse == -1) {
						firstFalse = x;
					}
				}
			}
			
			if (numFalse == numTrue && numCows == 2) {
				// Special case, output the top left cow
				outX = 0;
				outY = 0;
				return;
			} else if (numTrue == 1 && firstTrue != -1) {
				// One true cow found
				if (outFound) {
					// Multiple wrong cows; If they are in the same row, answer is the top row cow
					if (outX != firstTrue) {
						outX = -1;
						outY = -1;
						return;
					} else {
						outY = 0;
					}
				} else {
					outX = firstTrue;
					outY = y;
					outFound = true;
				}
			} else if (numFalse == 1 && firstFalse != -1) {
				// One false cow found
				if (outFound) {
					// Multiple wrong cows; If they are in the same row, answer is the top row cow
					if (outX != firstFalse) {
						outX = -1;
						outY = -1;
						return;
					} else {
						outY = 0;
					}
				} else {
					outX = firstFalse;
					outY = y;
					outFound = true;
				}
			} else if ((numTrue > numFalse && numFalse > 1) || (numFalse > numTrue && numTrue > 1)) {
				// More than one wrong cow...? Impossible!
				outX = -1;
				outY = -1;
				return;
			}
		}
	}
	
	void fixFirstRow() {
		for (int x = 0; x < numCows; x++) {
			if (!cows[0][x]) {
				flipColumn(x);
			}
		}
	}
	
	void flipColumn(int x) {
		for (int y = 0; y < numCows; y++) {
			cows[y][x] = !cows[y][x];
		}
	}
	
	void flipRow(int y) {
		for (int x = 0; x < numCows; x++) {
			cows[y][x] = !cows[y][x];
		}
	}
	
	void getInput() throws IOException {
		BufferedReader s = new BufferedReader(new FileReader("leftout.in"));
		numCows = Integer.parseInt(s.readLine());
		
		// Fill cows array
		cows = new boolean[numCows][numCows];
		
		String line;
		for (int y = 0; y < numCows; y++) {
			line = s.readLine();
			for (int x = 0; x < numCows; x++) {
				cows[y][x] = (line.charAt(x) == 'R' ? true : false);
			}
		}
		
		s.close();
	}
	
	public static void main(String[] args) throws IOException {
		new leftout();
	}
	
}
