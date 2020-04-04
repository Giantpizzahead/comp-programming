/*
ID: sunnyky1
LANG: JAVA 
TASK: friday
*/

import java.io.*;

public class friday {
	static int[] daysInMonth = new int[] {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	static int[] numPerDay = new int[7];
	static int n, currDay;
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("friday.in"));
		n = Integer.parseInt(fin.readLine());
		fin.close();
		currDay = 0;
		// First, figure out what day January 13th lies on
		currDay = (currDay + 12) % 7;
		
		for (int i = 0; i < n; i++) {
			runYear(1900 + i);
		}
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("friday.out")));
		StringBuilder output = new StringBuilder();
		for (int i = 0; i < 7; i++) {
			output.append(numPerDay[(i + 5) % 7] + " ");
		}
		output.deleteCharAt(output.length() - 1);
		fout.println(output.toString());
		fout.close();
	}
	
	static void runYear(int year) {
		// Iterate through all the months
		for (int m = 0; m < 12; m++) {
			numPerDay[currDay]++;
			if (daysInMonth[m] != -1) {
				currDay = (currDay + daysInMonth[m]) % 7;
			} else {
				currDay = (currDay + februaryDays(year)) % 7;
			}
		}
	}
	
	static int februaryDays(int year) {
		if (year % 4 == 0 && (!(year % 100 == 0) || year % 400 == 0)) {
			// Leap year
			return 29;
		} else {
			// Not a leap year
			return 28;
		}
	}

}
