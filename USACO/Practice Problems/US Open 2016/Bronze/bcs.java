import java.util.*;
import java.io.*;

public class bcs {
	
	public static Piece original;
	public static Piece[] pieces;
	public static ArrayList<Pair> pairs;
	public static int pieceSizes, numPieces, piece1, piece2;

	public static void main(String[] args) throws IOException {
		getInput();
		findPossiblePairs();
		boolean worked;
		for (Pair pair : pairs) {
			// System.out.println("Testing pair " + pair.a + " " + pair.b);
			worked = testPair(pair);
			if (worked) {
				// Found the correct pair
				piece1 = Math.min(pair.a, pair.b);
				piece2 = Math.max(pair.a, pair.b);
				// System.out.println("Worked: " + piece1 + " " + piece2);
				break;
			} else {
				// System.out.println("Didn't work");
			}
		}
		
		PrintWriter fout = new PrintWriter("bcs.out");
		fout.println((piece1 + 1) + " " + (piece2 + 1));
		fout.close();
	}
	
	public static boolean testPair(Pair pair) {
		// Tests two pieces by trying every shift combination for both pieces
		Piece a = pieces[pair.a];
		Piece b = pieces[pair.b];
		boolean aFilled, bFilled, broke;
		for (int sxA = -a.leftShiftX; sxA <= a.rightShiftX; sxA++) {
			for (int syA = -a.downShiftY; syA <= a.upShiftY; syA++) {
				for (int sxB = -b.leftShiftX; sxB <= b.rightShiftX; sxB++) {
					for (int syB = -b.downShiftY; syB <= b.upShiftY; syB++) {
						broke = false;
						
						// System.out.printf("Testing shifts: %d %d %d %d\n", sxA, syA, sxB, syB);
						checkLoop:
						for (int y = 0; y < pieceSizes; y++) {
							for (int x = 0; x < pieceSizes; x++) {
								// Check whether piece a and piece b have a # here
								aFilled = inBounds(x-sxA, y+syA) && a.grid[y+syA][x-sxA] == 1;
								bFilled = inBounds(x-sxB, y+syB) && b.grid[y+syB][x-sxB] == 1;
								// System.out.println(aFilled + " " + bFilled);
								// Check if the given #s are valid
								if ((original.grid[y][x] == 1 && (aFilled ^ bFilled)) ||
									(original.grid[y][x] == 0 && !aFilled && !bFilled)) {
									// Valid; continue
									// System.out.println(y + " " + x + " valid");
								} else {
									// Not valid; try next shift
									// System.out.println(y + " " + x + " not valid");
									broke = true;
									break checkLoop;
								}
							}
						}
						
						if (!broke) {
							// Got to the end: It's a valid pair
							return true;
						}
						
					}
				}
			}
		}
		return false;
	}
	
	public static boolean inBounds(int x, int y) {
		// Returns true if the given (x, y) is in the piece bounds.
		return x >= 0 && x < pieceSizes && y >= 0 && y < pieceSizes;
	}
	
	public static void findPossiblePairs() {
		pairs = new ArrayList<Pair>();
		int targetSum = original.numFilled;
		for (int i = 0; i < numPieces; i++) {
			for (int j = i + 1; j < numPieces; j++) {
				if (pieces[i].numFilled + pieces[j].numFilled == targetSum) {
					// Possible pair, since the # of hashtags matches
					pairs.add(new Pair(i, j));
				}
			}
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader b = new BufferedReader(new FileReader("bcs.in"));
		String[] lineS = b.readLine().split(" ");
		pieceSizes = Integer.parseInt(lineS[0]);
		numPieces = Integer.parseInt(lineS[1]);
		
		// Parse the original piece
		original = new Piece();
		String line;
		for (int y = 0; y < pieceSizes; y++) {
			line = b.readLine();
			for (int x = 0; x < pieceSizes; x++) {
				original.grid[y][x] = (line.charAt(x) == '#') ? 1 : 0;
				if (original.grid[y][x] == 1) {
					original.numFilled++;
				}
				// System.out.print(original.grid[y][x]);
			}
			// System.out.println();
		}
		
		// Parse the broken pieces
		pieces = new Piece[numPieces];
		for (int i = 0; i < numPieces; i++) {
			// System.out.println();
			pieces[i] = new Piece();
			for (int y = 0; y < pieceSizes; y++) {
				line = b.readLine();
				for (int x = 0; x < pieceSizes; x++) {
					pieces[i].grid[y][x] = (line.charAt(x) == '#') ? 1 : 0;
					if (pieces[i].grid[y][x] == 1) {
						pieces[i].numFilled++;
					}
					// System.out.print(pieces[i].grid[y][x]);
				}
				// System.out.println();
			}
			pieces[i].findMaxShifts();
			// System.out.println();
		}
		
		b.close();
	}
	
	static class Piece {
		int[][] grid;
		int numFilled, leftShiftX, rightShiftX, upShiftY, downShiftY;
		
		public Piece() {
			grid = new int[pieceSizes][pieceSizes];
			numFilled = 0;
		}
		
		public void findMaxShifts() {
			// Finds the max possible shifts in every direction.
			leftShiftX = pieceSizes - 1;
			rightShiftX = pieceSizes - 1;
			upShiftY = pieceSizes - 1;
			downShiftY = pieceSizes - 1;
			for (int y = 0; y < pieceSizes; y++) {
				for (int x = 0; x < pieceSizes; x++) {
					if (grid[y][x] == 1) {
						// Change shifts
						leftShiftX = Math.min(x, leftShiftX);
						rightShiftX = Math.min(pieceSizes - 1 - x, rightShiftX);
						upShiftY = Math.min(y, upShiftY);
						downShiftY = Math.min(pieceSizes - 1 - y, downShiftY);
					}
				}
			}
			// System.out.printf("Piece shifts: %d %d %d %d\n", leftShiftX, rightShiftX, upShiftY, downShiftY);
		}
	}
	
	static class Pair {
		int a, b;
		public Pair(int a, int b) {
			this.a = a;
			this.b = b;
		}
	}

}
