import java.util.*;
import java.io.*;

public class Sleepy {
	int[] cows, steps;
	ArrayList<Integer> sortedCows;
	int numCows, stepsNeeded;
	
	public Sleepy() throws IOException {
		getInput();
		setupSorted();
		calculateSteps();
		
		/*
		System.out.println(sortedCows.toString());
		System.out.println(Arrays.toString(steps));
		*/
		
		PrintWriter fout = new PrintWriter("sleepy.out");
		fout.println(stepsNeeded);
		for (int i = 0; i < stepsNeeded - 1; i++) {
			fout.print(steps[i] + " ");
		}
		
		// Fix extra space issue
		if (stepsNeeded != 0) {
			fout.print(steps[stepsNeeded - 1]);
		}
		fout.println();
		
		fout.close();
	}
	
	void calculateSteps() {
		steps = new int[stepsNeeded];
		int currCow;
		for (int i = 0; i < stepsNeeded; i++) {
			currCow = cows[i];
			// Find the right index in sortedCows to insert this cow, and insert it
			steps[i] = numCows - sortedCows.size() - 1 + insertCow(currCow);
			
			// System.out.println(sortedCows);
		}
	}
	
	int insertCow(int cow) {
		int insertIndex = Collections.binarySearch(sortedCows, cow);
		if (insertIndex < 0) {
			insertIndex = -insertIndex - 1;
		}
		
		sortedCows.add(insertIndex, cow);
		// System.out.println("Inserted cow " + cow + " at index " + insertIndex);
		return insertIndex;
	}
	
	void setupSorted() {
		int lastNum = -1;
		sortedCows = new ArrayList<Integer>();
		for (int c : cows) {
			if (c > lastNum) {
				lastNum = c;
			} else {
				sortedCows.clear();
			}
			lastNum = c;
			sortedCows.add(c);
		}

		stepsNeeded = numCows - sortedCows.size();
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("sleepy.in"));
		numCows = Integer.parseInt(fin.readLine());
		cows = new int[numCows];
		String[] line = fin.readLine().split(" ");
		for (int i = 0; i < numCows; i++) {
			cows[i] = Integer.parseInt(line[i]);
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		new Sleepy();
	}

}
