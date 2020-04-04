/**
 * USACO 2018 December Contest, Gold
 * Problem 2. Cowpatibility
 * 
 * Ok, so I've thought about the problem a bit more now.
 * I think I have a method to do this in O(32N) time.
 * It involves a lot of weird combinatoric math stuff.
 * 
 * Let's try it!
 */

import java.util.*;
import java.io.*;

public class cowpatibility {
	HashMap<String, Integer> currCows;
	int[][] cowFavorites;
	int numCows;
	final int numFavoritesEach = 5;
	final boolean DEBUG = false;

	public cowpatibility() throws IOException {
		getInput();
		long answer = solve();
		
		if (DEBUG) System.out.println(answer);
		
		PrintWriter fout = new PrintWriter("cowpatibility.out");
		fout.println(answer);
		fout.close();
	}
	
	long solve() {
		long numPairs = 0;
		currCows = new HashMap<String, Integer>();
		
		// Add the first cow to the map for initialization purposes
		addCowToMap(0);
		
		for (int i = 1; i < numCows; i++) {
			numPairs += compareAndAddCow(i);
		}
		
		// Wanted answer is number of pairs that aren't compatible, so reverse the answer
		return ((long) (numCows - 1) * (long) numCows / 2) - numPairs;
	}
	
	/**
	 * Combines the two functions below to make the program more efficient.
	 */
	int compareAndAddCow(int cowi) {
		int numPairs = 0;
		Queue<State> toEval = new LinkedList<State>();
		
		// Add initial pairs to evaluate (one number only)
		for (int i = 0; i < numFavoritesEach; i++) {
			toEval.add(new State(Integer.toString(cowFavorites[cowi][i]), 1, i+1));
		}
		
		// Test all combinations
		State curr;
		String s;
		int n, i, v;
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			s = curr.s;
			n = curr.n;
			i = curr.i;
			
			// Get current value of this combo in the HashMap (if there is one)
			v = currCows.getOrDefault(s, 0);
			
			// Determine whether to add or subtract this amount (even or odd # of elements)
			if (n % 2 == 1) {
				// Odd; Add it
				numPairs += v;
			} else {
				// Even; Subtract it
				numPairs -= v;
			}
			
			// Add 1 to HashMap with current value (or default to 1 if not there yet)
			currCows.put(s, currCows.getOrDefault(s, 0) + 1);
			
			// Try adding every next number (to add all combinations)
			for (int j = i; j < numFavoritesEach; j++) {
				toEval.add(new State(s + " " + cowFavorites[cowi][j], n+1, j+1));
			}
		}
		
		return numPairs;
	}
	
	/**
	 * Adds all possible combinations of the given cow's favorite flavors to the HashMap.
	 * (+1 for each)
	 * 
	 * Does this using a somewhat recursive algorithm.
	 */
	void addCowToMap(int cowi) {
		Queue<State> toEval = new LinkedList<State>();
		
		// Add initial pairs to evaluate (one number only)
		for (int i = 0; i < numFavoritesEach; i++) {
			toEval.add(new State(Integer.toString(cowFavorites[cowi][i]), 1, i+1));
		}
		
		// Add all combinations
		State curr;
		String s;
		int n, i;
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			s = curr.s;
			n = curr.n;
			i = curr.i;
			
			// Add 1 to HashMap with current value (or default to 1 if not there yet)
			currCows.put(s, currCows.getOrDefault(s, 0) + 1);
			
			// Try adding every next number (to add all combinations)
			for (int j = i; j < numFavoritesEach; j++) {
				toEval.add(new State(s + " " + cowFavorites[cowi][j], n+1, j+1));
			}
		}
	}
	
	/**
	 * Uses combination and set rules to compare the current cow to the HashMap, and figure
	 * out how many pairs of cows the new cow is compatible with.
	 */
	int compareCowToMap(int cowi) {
		int numPairs = 0;
		Queue<State> toEval = new LinkedList<State>();
		
		// Add initial pairs to evaluate (one number only)
		for (int i = 0; i < numFavoritesEach; i++) {
			toEval.add(new State(Integer.toString(cowFavorites[cowi][i]), 1, i+1));
		}
		
		// Test all combinations
		State curr;
		String s;
		int n, i, v;
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			s = curr.s;
			n = curr.n;
			i = curr.i;
			
			// Get current value of this combo in the HashMap (if there is one)
			v = currCows.getOrDefault(s, 0);
			
			// Determine whether to add or subtract this amount (even or odd # of elements)
			if (n % 2 == 1) {
				// Odd; Add it
				numPairs += v;
			} else {
				// Even; Subtract it
				numPairs -= v;
			}
			
			// Try adding every next number (to add all combinations)
			for (int j = i; j < numFavoritesEach; j++) {
				toEval.add(new State(s + " " + cowFavorites[cowi][j], n+1, j+1));
			}
		}
		
		return numPairs;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("cowpatibility.in"));
		numCows = Integer.parseInt(fin.readLine());
		
		cowFavorites = new int[numCows][numFavoritesEach];
		
		// Parse all the cows' favorite flavors, sorting in increasing order for each
		String[] line;
		for (int i = 0; i < numCows; i++) {
			line = fin.readLine().split(" ");
			
			for (int j = 0; j < numFavoritesEach; j++) {
				cowFavorites[i][j] = Integer.parseInt(line[j]);
			}
			
			Arrays.sort(cowFavorites[i]);
		}
		
		if (DEBUG) System.out.println(Arrays.deepToString(cowFavorites));
		
		fin.close();
	}
	
	public static void main(String[] args) throws IOException {
		new cowpatibility();
	}
	
	class State {
		String s;
		int n, i;
		public State(String s, int n, int i) {
			this.s = s;
			this.n = n;
			this.i = i;
		}
	}
}
