import java.util.*;
import java.io.*;

public class mountains {
	
	public static Loc[] mountains;
	public static int numMountains;
	public static int INF = 999999999;

	public static void main(String[] args) throws IOException {
		// Parse input
		BufferedReader fin = new BufferedReader(new FileReader("mountains.in"));
		numMountains = Integer.parseInt(fin.readLine());
		mountains = new Loc[numMountains];
		String[] line;
		for (int i = 0; i < numMountains; i++) {
			line = fin.readLine().split(" ");
			mountains[i] = new Loc(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
		}
		fin.close();
		
		// Solve the problem
		// Sort all mountain peaks by decreasing y - x, breaking ties with decreasing y + x
		Arrays.sort(mountains, new LocComp());
		
		// Iterate through array
		int numCanSee = 0;
		int maxPlusVal = -INF;
		for (Loc m : mountains) {
			// Check if current mountain is obscured
			if (m.y + m.x <= maxPlusVal) {
				// Mountain is obscured
				// System.out.println("Mountain at " + m.x + " " + m.y + " is obscured");
			} else {
				// Mountain is not obscured; change values if needed
				// System.out.println("Mountain at " + m.x + " " + m.y + " is not obscured");
				numCanSee++;
				maxPlusVal = Math.max(maxPlusVal, m.y + m.x);
			}
		}
		
		// Output to file
		PrintWriter fout = new PrintWriter("mountains.out");
		fout.println(numCanSee);
		fout.close();
	}
	
	static class Loc {
		int x, y;
		public Loc(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	static class LocComp implements Comparator<Loc> {
		
		@Override
		public int compare(Loc l1, Loc l2) {
			// Sort by decreasing y - x, breaking ties with decreasing y + x
			if (l1.y - l1.x < l2.y - l2.x) {
				return 1;
			} else if (l1.y - l1.x > l2.y - l2.x) {
				return -1;
			} else if (l1.y + l1.x < l2.y + l2.x) {
				return 1;
			} else if (l1.y + l1.x > l2.y + l2.y) {
				return -1;
			} else {
				return 0;
			}
		}
		
	}

}
