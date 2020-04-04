/**
 * USACO 2018 December Contest - Gold
 * Problem 2. Cowpatibility
 * 
 * I have no clue how to do this one in less than O(N^2) time.
 * I'm gonna implement the n squared version; hopefully it gives me
 * some clues.
 */

import java.util.*;
import java.io.*;

public class cowpatibilitySlow {
	int[][] cowFavorites;
	HashSet<Integer>[] flavors;
	int numCows;
	
	cowpatibilitySlow() throws IOException {
		getInput();
		long answer = countPairs();
		
		System.out.println(answer);
		PrintWriter fout = new PrintWriter("cowpatibility.out");
		fout.println(answer);
		fout.close();
	}
	
	long countPairs() {
		long answer = 0;
		
		HashSet<Integer> compatibleCows = new HashSet<Integer>();
		for (int i = 0; i < numCows; i++) {
			compatibleCows.clear();
			for (int f : cowFavorites[i]) {
				compatibleCows.addAll(flavors[f]);
			}
			answer += numCows - compatibleCows.size();
			
			// System.out.println(compatibleCows);
		}
		
		return answer / 2;
	}
	
	@SuppressWarnings("unchecked")
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("cowpatibility.in"));
		numCows = Integer.parseInt(fin.readLine());
		int[] f = new int[5];
		String[] line;
		flavors = new HashSet[1000000];
		cowFavorites = new int[numCows][5];
		int x;
		
		// Make an array of HashSets with which cows like which ice cream flavors
		for (int i = 0; i < numCows; i++) {
			line = fin.readLine().split(" ");
			f[0] = Integer.parseInt(line[0]);
			f[1] = Integer.parseInt(line[1]);
			f[2] = Integer.parseInt(line[2]);
			f[3] = Integer.parseInt(line[3]);
			f[4] = Integer.parseInt(line[4]);
			
			for (int j = 0; j < 5; j++) {
				x = f[j];
				cowFavorites[i][j] = x;
				if (flavors[x] == null) {
					flavors[x] = new HashSet<Integer>();
				}
				flavors[x].add(i);
			}
		}
		
		fin.close();
	}
	
	
	public static void main(String[] args) throws IOException {
		new cowpatibilitySlow();
	}
	
}
