/*
ID: sunnyky1
LANG: JAVA
TASK: dualpal
*/

import java.io.*;
import java.util.*;

public class dualpal {
	static int N, S;
	static char[] BASE_NUMS = "0123456789".toCharArray();

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("dualpal.in"));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		N = Integer.parseInt(st.nextToken());
		S = Integer.parseInt(st.nextToken());
		fin.close();
		
		int numNumsFound = 0;
		int currNum = S + 1;
		boolean palindrome = false;
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("dualpal.out")));
		String convPow;
		while (numNumsFound < N) {
			palindrome = false;
			for (int b = 2; b <= 10; b++) {
				convPow = convBase(currNum, b);
				if (isPalindrome(convPow)) {
					if (!palindrome) palindrome = true;
					else {
						fout.println(currNum);
						numNumsFound++;
						break;
					}
				}
			}
			currNum++;
		}
		fout.close();
	}
	
	static String convBase(int num, int B) {
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
