import java.util.*;
import java.io.*;

public class nocross {
	
	public static int[] leftFields, rightFields;
	public static int[][] dpTable;
	public static int numBreeds;
	public static boolean debug;

	public static void main(String[] args) throws IOException {
		getInput();
		fillDPTable();
		FileWriter fout = new FileWriter("nocross.out");
		if (debug) {
			System.out.println(dpTable[numBreeds-1][numBreeds-1]);
		} else {
			fout.write(dpTable[numBreeds-1][numBreeds-1] + "\n");
		}
		fout.close();
	}
	
	public static void fillDPTable() {
		dpTable = new int[numBreeds][numBreeds];
		dpTable[0][0] = 0;
		int max;
		for (int l = 0; l < numBreeds; l++) {
			for (int r = 0; r < numBreeds; r++) {
				max = 0;
				if (l-1 >= 0) {
					max = dpTable[l-1][r];
				}
				if (r-1 >= 0) {
					max = Math.max(max, dpTable[l][r-1]);
				}
				if (Math.abs(leftFields[l] - rightFields[r]) < 5) {
					if (l-1 < 0 || r-1 < 0) {
						max = 1;
					} else {
						max = Math.max(max, dpTable[l-1][r-1] + 1);
					}
				}
				dpTable[l][r] = max;
			}
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader s = new BufferedReader(new FileReader("nocross.in"));
		numBreeds = Integer.parseInt(s.readLine());
		leftFields = new int[numBreeds];
		rightFields = new int[numBreeds];
		for (int i = 0; i < numBreeds; i++) {
			leftFields[i] = Integer.parseInt(s.readLine());
		}
		for (int i = 0; i < numBreeds; i++) {
			rightFields[i] = Integer.parseInt(s.readLine());
		}
		s.close();
	}

}
