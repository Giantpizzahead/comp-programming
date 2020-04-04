/*
ID: sunnyky1
LANG: JAVA
TASK: gift1
*/

import java.util.*;
import java.io.*;

public class gift1 {
	static HashMap<String, Integer> money;
	static String[] people;
	static int np;

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("gift1.in"));
		np = Integer.parseInt(fin.readLine());
		money = new HashMap<String, Integer>(np, 1);
		people = new String[np];
		for (int i = 0; i < np; i++) {
			people[i] = fin.readLine();
			money.put(people[i], 0);
		}
		// Simulate all gifts
		String giver, receiver;
		int amountToGive, numPeople;
		StringTokenizer st;
		for (int i = 0; i < np; i++) {
			giver = fin.readLine();
			st = new StringTokenizer(fin.readLine());
			amountToGive = Integer.parseInt(st.nextToken());
			numPeople = Integer.parseInt(st.nextToken());
			if (numPeople != 0) {
				amountToGive -= amountToGive % numPeople;
				money.put(giver, money.get(giver) - amountToGive);
				for (int j = 0; j < numPeople; j++) {
					receiver = fin.readLine();
					money.put(receiver, money.get(receiver) + amountToGive / numPeople);
				}
			}
		}
		fin.close();
		
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("gift1.out")));
		for (String person : people) {
			fout.println(person + " " + money.get(person));
		}
		fout.close();
	}

}
