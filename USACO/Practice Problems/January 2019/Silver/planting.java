import java.io.*;

public class planting {
	
	public static int[] numPathways;
	public static int maxSoFar, numFields;

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("planting.in"));
		numFields = Integer.parseInt(fin.readLine());
		numPathways = new int[numFields];
		maxSoFar = 0;
		int a, b;
		String[] line;
		for (int i = 0; i < numFields - 1; i++) {
			line = fin.readLine().split(" ");
			a = Integer.parseInt(line[0]) - 1;
			b = Integer.parseInt(line[1]) - 1;
			numPathways[a]++;
			numPathways[b]++;
			maxSoFar = Math.max(maxSoFar, numPathways[a]);
			maxSoFar = Math.max(maxSoFar, numPathways[b]);
		}
		fin.close();
		
		PrintWriter fout = new PrintWriter("planting.out");
		fout.println(maxSoFar + 1);
		fout.close();
	}

}
