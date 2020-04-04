/*
ID: sunnyky1
LANG: JAVA
TASK: namenum
*/

import java.util.*;
import java.io.*;

public class namenum {
	HashSet<String> acceptableNames;
	ArrayList<String> answers;
	String[] phoneChars = new String[] {null, null, "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"};
	String serial;
	int[] serialNums;
	
	public namenum() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("namenum.in"));
		serial = fin.readLine();
		serialNums = new int[serial.length()];
		for (int i = 0; i < serial.length(); i++) {
			serialNums[i] = serial.charAt(i) - '0';
		}
		fin.close();
		fin = new BufferedReader(new FileReader("dict.txt"));
		// Parse all the acceptable names
		acceptableNames = new HashSet<String>();
		String line = fin.readLine();
		while (line != null) {
			acceptableNames.add(line);
			line = fin.readLine();
		}
		fin.close();
		
		answers = new ArrayList<String>();
		runSearch(0, new StringBuilder(""));
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("namenum.out")));
		if (answers.size() == 0) fout.println("NONE");
		else for (String answer : answers) fout.println(answer);
		fout.close();
	}
	
	void runSearch(int i, StringBuilder currStr) {
		if (i > serialNums.length - 1) {
			// Reached the end; add it if it's an acceptable answer
			String finalStr = currStr.toString();
			if (acceptableNames.contains(finalStr)) {
				// System.out.println(finalStr);
				answers.add(finalStr);
			}
			return;
		}
		
		// System.out.println(serialNums[i]);
		int currChar = serialNums[i];
		for (int c = 0; c < 3; c++) {
			runSearch(i+1, currStr.append(phoneChars[currChar].charAt(c)));
			currStr.deleteCharAt(currStr.length() - 1);
		}
	}

	public static void main(String[] args) throws IOException {
		new namenum();
	}

}
