/**
 * USACO 2019 January Contest, Gold
 * Problem 1. Cow Poetry
 * 
 * Practice for USACO Gold contests.
 *
 */

import java.io.*;
import java.util.*;

public class poetry {
	int[] wordsWithSylls, rhymeScheme;
	long[] linesWithSylls, linesWithRhyme;
	HashMap<Integer, ArrayList<Integer>> rhymeSylls;
	int numWords, numLines, numSylls;
	final long MOD = 1000000007;
	
	public poetry() throws IOException {
		getInput();
		calcLinesWithSylls();
		calcLinesWithRhyme();
		int answer = calcTotalWays();
		
		/*
		System.out.println(Arrays.toString(wordsWithSylls));
		System.out.println(Arrays.toString(linesWithSylls));
		System.out.println(Arrays.toString(linesWithRhyme));
		System.out.println(answer);
		*/
		
		PrintWriter fout = new PrintWriter("poetry.out");
		fout.println(answer);
		fout.close();
	}
	
	/**
	 * Calculates the total # of ways to create a valid poem.
	 */
	int calcTotalWays() {
		long answer = 1;
		long currLines;
		
		for (int scheme : rhymeScheme) {
			if (scheme == 0) continue;
			currLines = 0;
			
			// Try each possible rhyme class
			for (long numLines : linesWithRhyme) {
				currLines += powmod(numLines, scheme, MOD);
				if (currLines >= MOD) currLines -= MOD;
			}
			
			answer *= currLines;
			answer %= MOD;
		}
		
		return (int) answer;
	}
	
	/**
	 * Calculates the number of lines that are K syllables long, and end with a specific
	 * rhyme class.
	 */
	void calcLinesWithRhyme() {
		linesWithRhyme = new long[rhymeSylls.size()];
		
		int i = 0;
		long numLines;
		for (Map.Entry<Integer, ArrayList<Integer>> entry : rhymeSylls.entrySet()) {
			numLines = 0;
			for (int s : entry.getValue()) {
				numLines += linesWithSylls[numSylls - s];
				if (numLines >= MOD) numLines -= MOD;
			}
			
			linesWithRhyme[i] = numLines;
			i++;
		}
	}
	
	/**
	 * Calculates the number of lines that are n syllables long (n is from 0 to K).
	 */
	void calcLinesWithSylls() {
		linesWithSylls = new long[numSylls + 1];
		linesWithSylls[0] = 1;
		long numLines;
		
		for (int i = 1; i < numSylls + 1; i++) {
			numLines = 0;
			for (int j = i - 1; j >= 0; j--) {
				numLines += linesWithSylls[j] * (long) wordsWithSylls[i-j];
				numLines %= MOD;
			}
			
			linesWithSylls[i] = numLines;
		}
	}
	
	/**
	 * Does a modding power thing. I didn't know how to do this in a somewhat fast way,
	 * so I had to look it up. :(
	 * 
	 * Source for the algorithm: Khan Academy
	 */
	int powmod(long num, int pow, long mod) {
		// Convert the power into binary
		StringBuilder binpowBuild = new StringBuilder();
		while (pow > 0) {
			binpowBuild.append(pow % 2);
			pow /= 2;
		}
		
		String binpow = binpowBuild.reverse().toString();
		// Calculate each mod for the powers of two, and multiply to the answer if
		// needed
		long answer = 1;
		long lastMod = num;
		if (binpow.charAt(binpow.length() - 1) == '1') {
			answer = num;
		}
		long currMod;
		for (int k = 1; k < binpow.length(); k++) {
			currMod = (lastMod * lastMod) % mod;
			if (binpow.charAt(binpow.length() - 1 - k) == '1') {
				// Multiply to the answer
				answer *= currMod;
				answer %= mod;
			}
			lastMod = currMod;
		}
		
		return (int) answer;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("poetry.in"));
		String[] line = fin.readLine().split(" ");
		numWords = Integer.parseInt(line[0]);
		numLines = Integer.parseInt(line[1]);
		numSylls = Integer.parseInt(line[2]);
		
		// Parse all the words
		wordsWithSylls = new int[numSylls + 1];
		rhymeSylls = new HashMap<Integer, ArrayList<Integer>>();
		int ns, rc;
		for (int i = 0; i < numWords; i++) {
			line = fin.readLine().split(" ");
			ns = Integer.parseInt(line[0]);
			rc = Integer.parseInt(line[1]);
			
			wordsWithSylls[ns]++;
			if (!rhymeSylls.containsKey(rc)) {
				rhymeSylls.put(rc, new ArrayList<Integer>());
			}
			rhymeSylls.get(rc).add(ns);
		}
		
		// Parse all the rhyme schemes
		rhymeScheme = new int[26];
		for (int i = 0; i < numLines; i++) {
			rhymeScheme[fin.readLine().charAt(0) - 'A']++;
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new poetry();
	}

}
