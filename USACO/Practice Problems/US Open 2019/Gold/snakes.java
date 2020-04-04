import java.util.*;
import java.io.*;

public class snakes {
	
	public static int[][][] dp;
	public static int[][] minCosts;
	public static int[] snakes, iToSize;
	public static HashMap<Integer, Integer> sizeToI;
	public static int numGroups, numUniqueSizes, numChanges, cc;
	public static int INF = Integer.MAX_VALUE / 2;

	public static void main(String[] args) throws IOException {
		getInput();
		fillDP();
		int answer = getAnswer();
		
		// System.out.println(answer);
		
		PrintWriter fout = new PrintWriter("snakes.out");
		fout.println(answer);
		fout.close();
	}
	
	public static int getAnswer() {
		int minCost = INF;
		
		// Go through all dp entries in the last index to get the final answer
		for (int j = sizeToI.get(snakes[numGroups - 1]); j < numUniqueSizes; j++) {
			minCost = Math.min(minCost, dp[1-cc][j][0]);
		}
		
		return minCost;
	}
	
	public static void fillDP() {
		dp = new int[2][numUniqueSizes][numChanges+1];
		minCosts = new int[numGroups][numChanges+1];
		
		// Keep track of minCosts to avoid having to repeatedly traverse the array
		for (int i = 0; i < numGroups; i++) {
			for (int j = 0; j < numChanges + 1; j++) {
				minCosts[i][j] = INF;
			}
		}
		
		// Initialize base cases (Index 0, all possible net sizes, starting cost)
		for (int j = 0; j < sizeToI.get(snakes[0]); j++) {
			dp[0][j][numChanges] = INF;
		}
		for (int j = sizeToI.get(snakes[0]); j < numUniqueSizes; j++) {
			dp[0][j][numChanges] = iToSize[j] - snakes[0];
		}
		
		// Main DP loop
		// Use currColumn tracker to save memory space
		int minCost, minAddedCost;
		cc = 1;
		for (int i = 1; i < numGroups; i++) {
			for (int j = 0; j < numUniqueSizes; j++) {
				for (int k = 0; k < numChanges + 1; k++) {
					minCost = INF;
					
					// If bucket size is not changed (only works if snakes at current location is small enough!)
					if (iToSize[j] >= snakes[i]) {
						minCost = dp[1-cc][j][k] + iToSize[j] - snakes[i];
					}
					
					// If bucket size is changed (only works if numChanges is not at max)
					if (k != numChanges) {
						if (minCosts[i][k] != INF) {
							minCost = Math.min(minCost, minCosts[i][k]);
						} else {
							minAddedCost = INF;
							for (int j2 = sizeToI.get(snakes[i]); j2 < numUniqueSizes; j2++) {
								minAddedCost = Math.min(minAddedCost, dp[1-cc][j2][k+1] + iToSize[j2] - snakes[i]);
								minCosts[i][k] = minAddedCost;
								minCost = Math.min(minCost, minAddedCost);
							}
						}
					}
					
					// Set current dp value to min of those
					dp[cc][j][k] = minCost;
					// System.out.printf("minCost at %d %d %d is %d\n", i, iToSize[j], k, minCost);
				}
			}
			cc = 1 - cc;
		}
	}
	
	public static void getInput() throws IOException {
		Scanner s = new Scanner(new FileReader("snakes.in"));
		numGroups = s.nextInt();
		numChanges = s.nextInt();
		
		// Parse all snake snakes
		snakes = new int[numGroups];
		TreeSet<Integer> uniqueGroups = new TreeSet<Integer>();
		for (int i = 0; i < numGroups; i++) {
			snakes[i] = s.nextInt();
			uniqueGroups.add(snakes[i]);
		}
		
		// Make the iToSize and sizeToI maps
		numUniqueSizes = uniqueGroups.size();
		iToSize = new int[numUniqueSizes];
		sizeToI = new HashMap<Integer, Integer>();
		int i = 0;
		for (int size : uniqueGroups) {
			iToSize[i] = size;
			sizeToI.put(size, i);
			i++;
		}
		
		s.close();
	}

}
