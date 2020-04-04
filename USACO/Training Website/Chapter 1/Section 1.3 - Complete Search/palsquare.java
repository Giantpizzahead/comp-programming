/*
ID: sunnyky1
LANG: JAVA
TASK: palsquare
*/

import java.io.*;
import java.util.*;

public class palsquare {
	static int B;
	static char[] BASE_NUMS = "0123456789ABCDEFGHIJ".toCharArray();

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("palsquare.in"));
		B = Integer.parseInt(fin.readLine());
		fin.close();
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("palsquare.out")));
		String convPow;
		for (int i = 1; i <= 300; i++) {
			convPow = convBase((int) Math.pow(i, 2));
			if (isPalindrome(convPow)) {
				fout.println(convBase(i) + " " + convPow);
			}
		}
		fout.close();
	}
	
	static String convBase(int num) {
		Stack<Character> newString = new Stack<Character>();
		while (num > 0) {
			newString.add(BASE_NUMS[num % B]);
			num /= B;
		}
		char[] finalString = new char[newString.size()];
		for (int i = 0; i < finalString.length; i++) {
			finalString[i] = newString.pop();
		}
		return new String(finalString);
	}
	
	static boolean isPalindrome(String str) {
		for (int i = 0; i < str.length() / 2; i++) {
			if (str.charAt(i) != str.charAt(str.length() - 1 - i)) {
				return false;
			}
		}
		return true;
	}

}
