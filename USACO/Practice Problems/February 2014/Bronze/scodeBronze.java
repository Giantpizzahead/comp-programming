/**
 * USACO 2014 February Contest (Bronze -> Silver)
 * Problem 3. Secret Code
 * 
 * This is because why not.
 */

import java.util.*;
import java.io.*;

public class scodeBronze {
	HashMap<String, Integer>[] strings;
	String startingString;
	int startingLength;
	boolean DEBUG = false;
	boolean VISUAL_DEBUG = false;
	
	@SuppressWarnings("unchecked")
	scodeBronze() throws IOException {
		getInput();
		int answer = -1;
		strings = new HashMap[startingLength + 1];
		
		for (int i = 0; i < startingLength + 1; i++) {
			strings[i] = new HashMap<String, Integer>();
		}
		
		strings[startingLength].put(startingString, 1);
		
		for (int i = startingString.length(); i >= 2; i--) {
			if (VISUAL_DEBUG) System.out.print(strings[i].size() + " ");
			answer += runIteration(i);
		}
		
		if (VISUAL_DEBUG || DEBUG) System.out.println("\nAnswer: " + answer);
		
		PrintWriter fout = new PrintWriter("scode.out");
		fout.println(answer);
		fout.close();
	}
	
	int runIteration(int l) {
		int totalWays = 0;
		
		// Iterate through all strings of length l
		String string, newString;
		int numWays, strlen, newNumWays;
		for (Map.Entry<String, Integer> entry : strings[l].entrySet()) {
			string = entry.getKey();
			strlen = string.length();
			numWays = entry.getValue();
			
			if (DEBUG) {
				System.out.println("Checking string " + string);
				System.out.println("numWays: " + numWays);
			}
			
			totalWays += numWays;
			
			// Calculate new strings if the checked length is not 2
			if (l != 2) {
				
				// Generate all possible decrypted strings
				//for (int i = 0; i < (strlen - 1) / 2; i++) {
				for (int i = strlen / 2 - 1; i < (strlen - 1) / 2; i++) {
					// Partial string taken from left, added to left
					// Ex: abc -> ABabc
					if (string.substring(0, i+1).equals(string.substring(i+1, (i+1) * 2))) {
						// Add the # of ways to get this string to the # of ways to get the decrypted string
						newString = string.substring(i+1);
						newNumWays = strings[strlen - i - 1].getOrDefault(newString, 0) + numWays;
						if (DEBUG) System.out.println("New string " + newString + " num ways " + newNumWays);
						
						strings[strlen - i - 1].put(newString, newNumWays);
					}
					
					// Partial string taken from right, added to left
					// Ex: abc -> BCabc
					if (string.substring(0, i+1).equals(string.substring(strlen - i - 1))) {
						newString = string.substring(i+1);
						newNumWays = strings[strlen - i - 1].getOrDefault(newString, 0) + numWays;
						if (DEBUG) System.out.println("New string " + newString + " num ways " + newNumWays);
						
						strings[strlen - i - 1].put(newString, newNumWays);
					}
					
					// Partial string taken from left, added to right
					// Ex: abc -> abcAB
					if (string.substring(0, i+1).equals(string.substring(strlen - i - 1))) {
						newString = string.substring(0, strlen - i - 1);
						newNumWays = strings[strlen - i - 1].getOrDefault(newString, 0) + numWays;
						if (DEBUG) System.out.println("New string " + newString + " num ways " + newNumWays);
						
						strings[strlen - i - 1].put(newString, newNumWays);
					}
					
					// Partial string taken from right, added to right
					// Ex: abc -> abcBC
					if (string.substring(strlen - i - 1).equals(string.substring(strlen - 2 * (i + 1), strlen - i - 1))) {
						newString = string.substring(0, strlen - i - 1);
						newNumWays = strings[strlen - i - 1].getOrDefault(newString, 0) + numWays;
						if (DEBUG) System.out.println("New string " + newString + " num ways " + newNumWays);
						
						strings[strlen - i - 1].put(newString, newNumWays);
					}
				}
				
			}
		}
		
		if (DEBUG) System.out.println("Total ways for iteration " + l + ": " + totalWays);
		
		return totalWays;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("scode.in"));
		startingString = fin.readLine();
		startingLength = startingString.length();
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new scodeBronze();
	}

}
