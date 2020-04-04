/*
ID: sunnyky1
LANG: JAVA
TASK: beads
*/

import java.io.*;

public class beads {
	int[] beads;
	int n;
	
	public beads() throws IOException {
		getInput();
		// System.out.println(Arrays.toString(b));
		output(solve());
	}
	
	int solve() {
		int numLast = 0;
		int numCurr = 0;
		int typeCurr = beads[0];
		int numWhiteInRow = 0;
		int answer = 0;
		for (int b : beads) {
			// Track the # of same color in a row
			if (b == typeCurr || b == 2) {
				numCurr++;
			} else if (typeCurr == 2) {
				// Last ones were all white beads; set typeCurr to current type of bead
				typeCurr = b;
				numCurr++;
			} else {
				// Different color bead; update answer & move curr to last
				answer = Math.max(numLast + numCurr, answer);
				numLast = numCurr - numWhiteInRow;
				numCurr = numWhiteInRow + 1;
				typeCurr = b;
			}
			
			// Update numWhiteInRow
			if (b == 2) {
				// White bead; add to numWhiteInRow
				numWhiteInRow++;
			} else {
				// Reset counter
				numWhiteInRow = 0;
			}
		}
		
		// Continue going until the next cutoff point (loop back to the start)
		for (int b : beads) {
			// If the whole necklace can be gotten, return the full necklace
			if (numLast + numCurr == beads.length) return beads.length;
			
			// Track the # of same color in a row
			if (b == typeCurr || b == 2) {
				numCurr++;
			} else if (typeCurr == 2) {
				// Last ones were all white beads; set typeCurr to current type of bead
				typeCurr = b;
				numCurr++;
			} else {
				// Different color bead; update answer & break
				answer = Math.max(numLast + numCurr, answer);
				break;
			}
		}
		
		return answer;
	}
	
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("beads.in"));
		n = Integer.parseInt(fin.readLine());
		beads = new int[n];
		String beadStr = fin.readLine();
		fin.close();
		char bead;
		for (int i = 0; i < beadStr.length(); i++) {
			bead = beadStr.charAt(i);
			if (bead == 'r') beads[i] = 0;
			else if (bead == 'b') beads[i] = 1;
			else beads[i] = 2;
		}
	}
	
	void output(int answer) throws IOException {
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));
		fout.println(answer);
		fout.close();
	}

	public static void main(String[] args) throws IOException {
		new beads();
	}

}
