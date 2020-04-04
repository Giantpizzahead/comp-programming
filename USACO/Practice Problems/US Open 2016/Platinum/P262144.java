import java.util.*;
import java.io.*;

public class P262144 {
	ArrayList<Integer> nums;
	int numNums;

	public P262144() throws IOException {
		getInput();
		// Run the needed iterations
		// System.out.println(nums.toString());
		for (int i = 1; i <= 70; i++) {
			runIteration(i);
			/*
			System.out.println("After iteration " + i);
			System.out.println(nums.toString());
			*/
		}
		
		// Find the max value
		int max = 0;
		for (int n : nums) {
			max = Math.max(n, max);
		}
		
		PrintWriter fout = new PrintWriter("262144.out");
		fout.println(max);
		fout.close();
	}
	
	/**
	 * Combines all of the specified number (if possible), and updates the ArrayList.
	 */
	void runIteration(int target) {
		ArrayList<Integer> newNums = new ArrayList<Integer>();
		
		boolean onTarget = false;
		int numInARow = 0;
		for (int n : nums) {
			if (n == target && !onTarget) {
				// Start counting the # of target numbers in a row
				numInARow = 1;
				onTarget = true;
			} else if (n == target) {
				// Continue counting the # in a row
				numInARow++;
			} else if (onTarget) {
				// Just finished a row of target numbers
				// If even number of targets were found, add N/2 numbers with value target+1
				// If odd number of targets were found, add N/2 numbers with value target+1,
				// then a -1, then N/2 more numbers with value target+1 to try both possibilities
				if (numInARow % 2 == 0) {
					// Even
					for (int i = 0; i < numInARow / 2; i++) {
						newNums.add(target+1);
					}
				} else {
					// Odd
					for (int i = 0; i < numInARow / 2; i++) {
						newNums.add(target+1);
					}
					newNums.add(target);
					for (int i = 0; i < numInARow / 2; i++) {
						newNums.add(target+1);
					}
				}
				numInARow = 0;
				newNums.add(n);
			} else {
				// Last number was not a target number either; just add this one to the new list
				newNums.add(n);
			}
		}
		
		nums = newNums;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("262144.in"));
		numNums = Integer.parseInt(fin.readLine());
		nums = new ArrayList<Integer>(numNums);
		
		for (int i = 0; i < numNums; i++) {
			nums.add(Integer.parseInt(fin.readLine()));
		}
		
		// Fix edge case
		nums.add(-1);
		
		fin.close();
	}
	
	public static void main(String[] args) throws IOException {
		new P262144();
	}

}
