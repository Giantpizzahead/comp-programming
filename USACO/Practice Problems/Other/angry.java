import java.util.*;
import java.io.*;

public class angry {
	
	public static int[] neededLeft, neededRight, haybales;
	public static int numHaybales;
	public static int INF = 999999999;
	
	public static void main(String[] args) throws IOException {
		getInput();
		fillNeededLeft();
		fillNeededRight();
		
		/*
		for (int i = 0; i < numHaybales; i++) {
			System.out.print(neededLeft[i] + " ");
		}
		System.out.println();
		for (int i = 0; i < numHaybales; i++) {
			System.out.print(neededRight[i] + " ");
		}
		System.out.println();
		*/
		
		double answer = findAnswer();
		answer = Math.round(answer * 10f) / 10f;
		// System.out.printf("%.1f\n", answer);
		
		PrintWriter fout = new PrintWriter("angry.out");
		fout.printf("%.1f\n", answer);
		fout.close();
	}
	
	public static double findAnswer() {
		// Finds the answer by taking two haybales, and finding the minimum needed
		// power to clear the left of one and the right of the other.
		double leastPowerNeeded = (haybales[0] + haybales[numHaybales - 1]) / 2f;
		double powerNeeded;
		int i = 0;
		int j = numHaybales - 1;
		while (i < j) {
			powerNeeded = Math.max((haybales[j] - haybales[i]) / 2f, Math.max(neededLeft[i], neededRight[j]) + 1);
			leastPowerNeeded = Math.min(leastPowerNeeded, powerNeeded);
			if (neededLeft[i+1] < neededRight[j-1]) {
				i++;
			} else {
				j--;
			}
		}
		
		return leastPowerNeeded;
	}
	
	public static void fillNeededLeft() {
		// Fills the neededLeft array. Traverses from left to right in O(N) time.
		neededLeft = new int[numHaybales];
		int currPower = 0;
		int currMax = haybales[0];
		for (int i = 0; i < numHaybales; i++) {
			if (currMax > haybales[i]) {
				// No need to recalculate everything; Just use the currPower value
				neededLeft[i] = currPower;
			} else if (currMax == haybales[i]) {
				// Recalculate everything
				neededLeft[i] = currPower;
				currPower++;
				currMax = haybales[i] + currPower;
			} else {
				// This haybale is too far away; Set it's value manually
				currPower = Math.max(currPower + 1, haybales[i] - haybales[i-1]);
				neededLeft[i] = currPower;
				currPower++;
				currMax = haybales[i] + currPower;
			}
		}
	}
	
	public static void fillNeededRight() {
		// Fills the neededRight array. Traverses from right to left in O(N) time.
		// Basically a duplicate of fillNeededLeft().
		neededRight = new int[numHaybales];
		int currPower = 0;
		int currMax = haybales[numHaybales-1];
		for (int i = numHaybales - 1; i >= 0; i--) {
			if (currMax < haybales[i]) {
				// No need to recalculate everything; Just use the currPower value
				neededRight[i] = currPower;
			} else if (currMax == haybales[i]) {
				// Recalculate everything
				neededRight[i] = currPower;
				currPower++;
				currMax = haybales[i] - currPower;
			} else {
				// This haybale is too far away; Set it's value manually
				currPower = Math.max(currPower + 1, haybales[i+1] - haybales[i]);
				neededRight[i] = currPower;
				currPower++;
				currMax = haybales[i] - currPower;
			}
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("angry.in"));
		numHaybales = Integer.parseInt(fin.readLine());
		haybales = new int[numHaybales];
		for (int i = 0; i < numHaybales; i++) {
			haybales[i] = Integer.parseInt(fin.readLine());
		}
		// Sort the haybales array - O(N*log(N))
		Arrays.sort(haybales);
		
		fin.close();
	}

}
