import java.util.*;
import java.io.*;

public class walk {
	
	public static int numCows, numGroups;
	public static int INF = Integer.MAX_VALUE;

	public static void main(String[] args) throws IOException {
		getInput();
		int answer = generateMST();
		PrintWriter fout = new PrintWriter("walk.out");
		fout.println(answer);
		fout.close();
	}
	
	public static int generateMST() {
		// Generates an MST. Calculates edge weights on the fly.
		int[] distances = new int[numCows];
		for (int i = 0; i < numCows; i++) {
			distances[i] = INF;
		}
		distances[numCows - 1] = 0;
		boolean[] evaluated = new boolean[numCows];
		evaluated[numCows - 1] = true;
		
		// Main MST loop
		int curr = numCows - 1;
		int edgesLeft = numCows - numGroups + 1;
		int dist, nextCurr;
		int bestDist = INF;
		while (edgesLeft > 0) {
			// Check all neighbors while also finding the next node to evaluate
			nextCurr = -1;
			bestDist = INF;
			for (int i = 0; i < numCows; i++) {
				if (curr != i && !evaluated[i]) {
					// Calculate distance using their incredibly annoying formula
					dist = 2019201997 - 84 * Math.min(curr+1, i+1) - 48 * Math.max(curr+1, i+1);
					if (dist < distances[i]) {
						// New best distance found
						distances[i] = dist;
					}
					// Check if this is a better distance
					if (dist < bestDist) {
						// New best distance
						bestDist = dist;
						nextCurr = i;
					}
				}
			}
			edgesLeft--;
			evaluated[nextCurr] = true;
		}
		return bestDist;
	}
	
	public static void getInput() throws IOException {
		BufferedReader s = new BufferedReader(new FileReader("walk.in"));
		String[] line = s.readLine().split(" ");
		numCows = Integer.parseInt(line[0]);
		numGroups = Integer.parseInt(line[1]);
		s.close();
	}

}
