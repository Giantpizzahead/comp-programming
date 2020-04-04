/*
ID: sunnyky1
LANG: JAVA
TASK: test
*/

import java.util.*;
import java.io.*;

public class test {

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("test.in"));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		fin.close();
		
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("test.out")));
		fout.println((long) a + (long) b);
		fout.close();
	}

}
