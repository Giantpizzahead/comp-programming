/*
ID: sunnyky1
LANG: JAVA
TASK: ride
*/

import java.io.*;

public class ride {

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("ride.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("ride.out")));
		if (convert(fin.readLine()) % 47 == convert(fin.readLine()) % 47) {
			fout.println("GO");
		} else {
			fout.println("STAY");
		}
		fin.close();
		fout.close();
	}
	
	static int convert(String str) {
		byte[] bytes = str.getBytes();
		int num = 1;
		for (int i = 0; i < bytes.length; i++) {
			num *= (int) bytes[i] - 'A' + 1;
		}
		return num;
	}

}
