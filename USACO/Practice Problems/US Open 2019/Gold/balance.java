/**
 * USACO 2019 US Open Contest, Gold
 * Problem 3 - Balancing Inversions
 * 
 * For USACO prep.
 */

import java.io.*;
import java.util.*;

public class balance {
	
	static int leftZeroes, leftOnes, rightZeroes, rightOnes;
	static int leftInRow, rightInRow, leftEdge, rightEdge;
	static int leftInvs, rightInvs, numNums;
	static int[] left, right;
	static boolean DEBUG = false;

	public static void main(String[] args) throws IOException {
		getInput();
		fillStartingInfo();
		
		// Main loop
		int numMoves = 0;
		while (leftInvs != rightInvs) {
			numMoves += doBestMove();
		}
		
		if (DEBUG) System.out.println("Answer: " + numMoves);
		
		PrintWriter fout = new PrintWriter("balance.out");
		fout.println(numMoves);
		fout.close();
	}
	
	public static int doBestMove() {
		int leftNeeded1, rightNeeded1, leftNeeded2, rightNeeded2, invDist1, invDist2;
		
		// Move type: Switch 0 | 1
		leftNeeded1 = (leftEdge == 1) ? leftInRow : 0;
		rightNeeded1 = (rightEdge == 0) ? rightInRow : 0;
		invDist1 = Math.abs((leftInvs - leftOnes + leftNeeded1) - (rightInvs - rightZeroes + rightNeeded1));
		
		// Move type: Switch 1 | 0
		leftNeeded2 = (leftEdge == 0) ? leftInRow : 0;
		rightNeeded2 = (rightEdge == 1) ? rightInRow : 0;
		invDist2 = Math.abs((leftInvs + leftOnes - leftNeeded2) - (rightInvs + rightZeroes - rightNeeded2));
		
		// Choose the best move type out of the above two
		int bestInvDist, bestMoveType, movesNeeded;
		if (invDist1 < invDist2) {
			// Switch 0 | 1 is better
			bestMoveType = 0;
			bestInvDist = invDist1;
			movesNeeded = leftNeeded1 + rightNeeded1 + 1;
		} else if (invDist1 > invDist2) {
			// Switch 1 | 0 is better
			bestMoveType = 1;
			bestInvDist = invDist2;
			movesNeeded = leftNeeded2 + rightNeeded2 + 1;
		} else if (leftNeeded1 + rightNeeded1 < leftNeeded2 + rightNeeded2) {
			// Switch 0 | 1 takes less moves
			bestMoveType = 0;
			bestInvDist = invDist1;
			movesNeeded = leftNeeded1 + rightNeeded1 + 1;
		} else {
			// Switch 1 | 0 takes less moves, or they're the same so it doesn't matter
			bestMoveType = 1;
			bestInvDist = invDist2;
			movesNeeded = leftNeeded2 + rightNeeded2 + 1;
		}
		
		if (DEBUG) System.out.println(bestInvDist + " " + bestMoveType + " " + movesNeeded);

		// Compare the switch move with a standard 1-by-1 move
		if (bestInvDist > Math.max(Math.abs(leftInvs - rightInvs) - movesNeeded, 0)) {
			// Standard 1-by-1 is better, just do that for the rest of the moves
			if (DEBUG) System.out.println("Standard 1-by-1");
			bestInvDist = Math.abs(leftInvs - rightInvs);
			leftInvs = rightInvs;
			return bestInvDist;
		} else {
			// Switch is better, do that
			if (DEBUG) System.out.println("Switch");
			// Adjust variables as needed
			if (bestMoveType == 0) {
				// Switch 0 | 1
				leftInvs = leftInvs - leftOnes + leftNeeded1;
				rightInvs = rightInvs - rightZeroes + rightNeeded1;
				leftZeroes--;
				leftOnes++;
				rightZeroes++;
				rightOnes--;
				// Simulate the switch in the arrays
				left[numNums - 1 - leftNeeded1] = 1;
				right[rightNeeded1] = 0;
				if (leftEdge == 0) {
					leftEdge = 1;
				}
				if (rightEdge == 1) {
					rightEdge = 0;
				}
			} else {
				// Switch 1 | 0
				leftInvs = leftInvs + leftOnes - leftNeeded2;
				rightInvs = rightInvs + rightZeroes - rightNeeded2;
				leftZeroes++;
				leftOnes--;
				rightZeroes--;
				rightOnes++;
				// Simulate the switch in the arrays
				left[numNums - 1 - leftNeeded2] = 0;
				right[rightNeeded2] = 1;
				if (leftEdge == 1) {
					leftEdge = 0;
				}
				if (rightEdge == 0) {
					rightEdge = 1;
				}
			}
			
			// Recalculate consecutive numbers
			consecutiveLeft();
			consecutiveRight();
			
			return movesNeeded;
		}
	}
	
	public static void consecutiveLeft() {
		int check = left[numNums - 1];
		leftInRow = 0;
		for (int i = numNums - 1; i >= 0; i--) {
			if (check == left[i]) {
				leftInRow++;
			} else {
				break;
			}
		}
		if (DEBUG) System.out.println("consecutiveLeft() -> " + leftInRow);
	}
	
	public static void consecutiveRight() {
		int check = right[0];
		rightInRow = 0;
		for (int i = 0; i < numNums; i++) {
			if (check == right[i]) {
				rightInRow++;
			} else {
				break;
			}
		}
		if (DEBUG) System.out.println("consecutiveRight() -> " + rightInRow);
	}
	
	public static void fillStartingInfo() {
		
		// Fill in variables for left
		int stillInRow = left[numNums - 1];
		leftEdge = stillInRow;
		leftZeroes = 0;
		leftOnes = 0;
		leftInRow = 0;
		leftInvs = 0;
		for (int i = numNums - 1; i >= 0; i--) {
			if (left[i] == 0) {
				leftZeroes++;
				if (stillInRow == 0) {
					leftInRow++;
				} else {
					stillInRow = -1;
				}
			} else {
				leftOnes++;
				if (stillInRow == 1) {
					leftInRow++;
				} else {
					stillInRow = -1;
				}
				
				// Add inversions
				leftInvs += leftZeroes;
			}
		}
		
		if (DEBUG) System.out.printf("Left %d %d %d %d\n", leftZeroes, leftOnes, leftInRow, leftInvs);
		
		// Fill in variables for right
		stillInRow = right[0];
		rightEdge = stillInRow;
		rightZeroes = 0;
		rightOnes = 0;
		rightInRow = 0;
		rightInvs = 0;
		for (int i = 0; i < numNums; i++) {
			if (right[i] == 0) {
				rightZeroes++;
				if (stillInRow == 0) {
					rightInRow++;
				} else {
					stillInRow = -1;
				}
				
				// Add inversions
				rightInvs += rightOnes;
			} else {
				rightOnes++;
				if (stillInRow == 1) {
					rightInRow++;
				} else {
					stillInRow = -1;
				}
			}
		}
		
		consecutiveLeft();
		consecutiveRight();
		
		if (DEBUG) System.out.printf("Right %d %d %d %d\n", rightZeroes, rightOnes, rightInRow, rightInvs);
	}
	
	public static void getInput() throws IOException {
		Scanner s = new Scanner(new FileReader("balance.in"));
		numNums = s.nextInt();
		
		// Initialize both arrays
		left = new int[numNums];
		right = new int[numNums];
		for (int i = 0; i < numNums; i++) {
			left[i] = s.nextInt();
		}
		for (int i = 0; i < numNums; i++) {
			right[i] = s.nextInt();
		}
		
		s.close();
	}

}
