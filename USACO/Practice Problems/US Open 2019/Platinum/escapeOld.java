/**
 * USACO 2019 US Open - Platinum
 * Problem 2. Compound Escape
 * 
 * I wanted to try my hand at this problem. I think I have a solution, but I can't
 * work out the technical details of it.
 * 
 * For now, I'm going to try and implement an O(3^2K * N) or ~O(50000N) solution.
 * This is too slow for most test cases, but I'll try and optimize it later.
 */

import java.util.*;
import java.io.*;

public class escape {
	int[][] dp;
	int[][] perms;
	int[][] horEdges, vertEdges;
	int height, width, currentPerm;
	
	public escape() throws IOException {
		getInput();
		genPerms();
		System.out.println(Arrays.deepToString(horEdges));
		System.out.println(Arrays.deepToString(vertEdges));
		System.out.println();
		doDP();
	}
	
	void doDP() {
		// dp[rowNum][cowPermNum] = Min cost tree up to and including row rowNum
		// With given permutation of connected edges for the next row
		int numPerms = (int) Math.pow(3, width);
		dp = new int[height][numPerms];
		for (int r = 0; r < height; r++) {
			for (int p = 0; p < numPerms; p++) {
				
			}
		}
	}
	
	int getPermNum(int[] permArr) {
		int permNum = 0;
		int mult = 1;
		for (int i = width - 1; i >= 0; i--) {
			permNum += mult * permArr[i];
			mult *= 3;
		}
		
		return permNum;
	}
	
	void genPerms() {
		int[] currPerms = new int[width];
		perms = new int[(int) Math.pow(3, width)][width];
		currentPerm = 0;
		
		recPerms(currPerms, 0);
	}
	
	void recPerms(int[] currPerms, int index) {
		for (int i = 0; i < 3; i++) {
			currPerms[index] = i;
			if (index != width-1) {
				recPerms(currPerms, index+1);
			} else {
				perms[currentPerm] = currPerms.clone();
				currentPerm++;
			}
		}
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("escape.in"));
		String[] line = fin.readLine().split(" ");
		height = Integer.parseInt(line[0]);
		width = Integer.parseInt(line[1]);
		horEdges = new int[height][width - 1];
		vertEdges = new int[width][height - 1];
		
		// Parse all the edge costs
		for (int i = 0; i < height; i++) {
			line = fin.readLine().split(" ");
			horEdges[i] = Arrays.stream(line).mapToInt(x -> Integer.parseInt(x)).toArray();
		}
		
		for (int i = 0; i < width; i++) {
			line = fin.readLine().split(" ");
			vertEdges[i] = Arrays.stream(line).mapToInt(x -> Integer.parseInt(x)).toArray();
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new escape();
	}

}
