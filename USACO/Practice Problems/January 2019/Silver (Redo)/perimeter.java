import java.util.*;
import java.io.*;

public class perimeter {
	
	public static boolean[][] grid;
	public static boolean[][] visited;
	public static int gridSize, maxArea, minPerimeter;

	public static void main(String[] args) throws IOException {
		getInput();
		searchForBlobs();
		PrintWriter fout = new PrintWriter("perimeter.out");
		fout.println(maxArea + " " + minPerimeter);
		fout.close();
	}
	
	public static void blobBFS(int startY, int startX) {
		// Uses a queue to search through all blobs. Keeps track of visited cells to avoid double-counting stuff.
		Queue<Loc> toEval = new LinkedList<Loc>();
		toEval.add(new Loc(startY, startX));
		int currArea = 0;
		int currPerimeter = 0;
		
		// Main BFS loop
		Loc curr;
		int y, x, cy, cx;
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			y = curr.y;
			x = curr.x;
			currArea++;
			
			// Find neighbors
			for (int i = 0; i < 4; i++) {
				switch (i) {
				
				case 0:
					cx = 1;
					cy = 0;
					break;
				case 1:
					cx = -1;
					cy = 0;
					break;
				case 2:
					cx = 0;
					cy = 1;
					break;
				default:
					cx = 0;
					cy = -1;
					break;
				
				}
				
				// Look for ice cream in neighbor cell (if it's in the grid bounds)
				if (x + cx >= 0 && x + cx < gridSize && y + cy >= 0 && y + cy < gridSize && grid[y + cy][x + cx]) {
					// Found ice cream; add to BFS if not visited already
					if (!visited[y + cy][x + cx]) {
						visited[y + cy][x + cx] = true;
						toEval.add(new Loc(y + cy, x + cx));
					}
				} else {
					// No blob here; add to perimeter
					currPerimeter++;
				}
			}
		}
		
		// If current blob is better than previous blobs, make this blob the new best blob
		if (currArea > maxArea || (currArea == maxArea && currPerimeter < minPerimeter)) {
			maxArea = currArea;
			minPerimeter = currPerimeter;
		}
	}
	
	public static void searchForBlobs() {
		// Looks for a blob of ice cream. When it finds one, it calls blobBFS() with the found blob location.
		maxArea = 0;
		minPerimeter = 0;
		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				// Don't revisit cells that have already been explored
				if (!visited[y][x]) {
					visited[y][x] = true;
					if (grid[y][x]) {
						// Unexplored blob of ice cream found; traverse it
						// System.out.println("Exploring blob at " + y + " " + x);
						blobBFS(y, x);
					}
				}
			}
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("perimeter.in"));
		gridSize = Integer.parseInt(fin.readLine());
		grid = new boolean[gridSize][gridSize];
		visited = new boolean[gridSize][gridSize];
		// false = No ice cream, true = Ice cream
		String line;
		for (int y = 0; y < gridSize; y++) {
			line = fin.readLine();
			for (int x = 0; x < gridSize; x++) {
				grid[y][x] = (line.charAt(x) == '#');
			}
		}
		fin.close();
	}
	
	static class Loc {
		int y, x;
		public Loc(int y, int x) {
			this.y = y;
			this.x = x;
		}
	}

}
