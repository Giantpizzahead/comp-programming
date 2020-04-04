/**
 * 
 * USACO 2016 January Contest, Gold
 * Problem 2. Radio Contact
 * For DP Practice
 * @author Giantpizzahead
 *
 */

import java.io.*;

public class radio {
	
	public static long[][] dp;
	public static Loc[] johnLoc, bessieLoc;
	public static int johnMoves, bessieMoves;
	public static long INF = Long.MAX_VALUE / 4;

	public static void main(String[] args) throws IOException {
		getInput();
		fillDP();
		/*
		for (int i = 0; i < johnMoves + 1; i++) {
			for (int j = 0; j < bessieMoves + 1; j++) {
				System.out.print(dp[i][j] + " ");
			}
			System.out.println();
		}
		*/
		long answer = dp[johnMoves][bessieMoves];
		PrintWriter fout = new PrintWriter("radio.out");
		fout.println(answer);
		fout.close();
		// System.out.println(answer);
	}
	
	public static void fillDP() {
		dp = new long[johnMoves + 1][bessieMoves + 1];
		
		// Setup base cases
		for (int i = 0; i < johnMoves + 1; i++) {
			for (int j = 0; j < bessieMoves + 1; j++) {
				dp[i][j] = INF;
			}
		}
		dp[0][0] = 0;
		
		// Fill DP table
		long minSoFar;
		for (int i = 0; i < johnMoves + 1; i++) {
			for (int j = 0; j < bessieMoves + 1; j++) {
				minSoFar = INF;
				if (i-1 >= 0) {
					minSoFar = dp[i-1][j];
					if (j-1 >= 0) {
						minSoFar = Math.min(minSoFar, dp[i][j-1]);
						minSoFar = Math.min(minSoFar, dp[i-1][j-1]);
					}
				} else if (j-1 >= 0) {
					minSoFar = dp[i][j-1];
				}
				if (i == 0 && j == 0) {
					dp[i][j] = 0;
				} else {
					dp[i][j] = minSoFar + johnLoc[i].getDist(bessieLoc[j]);
				}
			}
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("radio.in"));
		String[] line = fin.readLine().split(" ");
		johnMoves = Integer.parseInt(line[0]);
		bessieMoves = Integer.parseInt(line[1]);
		
		// Parse starting locations
		johnLoc = new Loc[johnMoves + 1];
		bessieLoc = new Loc[bessieMoves + 1];
		line = fin.readLine().split(" ");
		johnLoc[0] = new Loc(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
		line = fin.readLine().split(" ");
		bessieLoc[0] = new Loc(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
		
		// Parse all moves
		String moveLine = fin.readLine();
		for (int i = 0; i < johnMoves; i++) {
			johnLoc[i+1] = new Loc(johnLoc[i], moveLine.charAt(i));
		}
		moveLine = fin.readLine();
		for (int i = 0; i < bessieMoves; i++) {
			bessieLoc[i+1] = new Loc(bessieLoc[i], moveLine.charAt(i));
		}
		
		fin.close();
	}
	
	static class Loc {
		int x, y;
		
		public Loc(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
		public Loc(Loc prev, char move) {
			switch (move) {
			case 'N':
				this.x = prev.x;
				this.y = prev.y + 1;
				break;
			case 'E':
				this.x = prev.x + 1;
				this.y = prev.y;
				break;
			case 'S':
				this.x = prev.x;
				this.y = prev.y - 1;
				break;
			case 'W':
				this.x = prev.x - 1;
				this.y = prev.y;
				break;
			}
		}
		
		public long getDist(Loc other) {
			return Math.round(Math.pow(other.x - x, 2) + Math.pow(other.y - y, 2));
		}
	}

}
