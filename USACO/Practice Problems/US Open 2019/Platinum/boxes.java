import java.util.ArrayList;
import java.util.HashSet;
import java.io.IOException;

public class boxes extends Grader {
	
	public ArrayList<Integer>[] connections;
	public int[] underWhich, underCount, depth, farmX, farmY;
	public boolean[] visited;
	public int numFarms = 0;
	public int numNotifys = 0;
	public int currUnder = 0;
	public int currX = 1;
	public int[][] lcaArr;
	
  	public static void main(String args[]) throws IOException { new boxes().run(); }
	
    // !------------------------------------------------!
  	// Comment this out before submittting!
  	// !------------------------------------------------!
  	/*
	public void run() {
  		super.testCase2();
  	}
  	 */
  	
  	
	@SuppressWarnings("unchecked")
	public void addRoad(int A, int B) {
		if (numFarms == 0) {
			numFarms = getN();
			connections = new ArrayList[numFarms];
			for (int i = 0; i < numFarms; i++) {
				connections[i] = new ArrayList<Integer>();
			}
		}
		
		connections[A].add(B);
		connections[B].add(A);
	}
	
	@Override
	public void buildFarms() {
		// Builds all the farms using the method on the drafting paper.
		// Start by traversing the tree, and setting the required values.
		traverseTree();
		
		/*
		for (int i = 0; i < numFarms; i++) {
			System.out.print(underWhich[i] + " ");
		}
		System.out.println();
		for (int i = 0; i < numFarms; i++) {
			System.out.print(underCount[i] + " ");
		}
		System.out.println();
		*/
		
		// Then, build the farms using the algorithm on the paper
		// Do this by doing another DFS
		visited = new boolean[numFarms];
		visited[0] = true;
		farmX = new int[numFarms];
		farmY = new int[numFarms];
		buildTree(0, 0);
		
		// Generate LCA array
		for (int i = 1; i < 18; i++) {
			for (int j = 0; j < numFarms; j++) {
				lcaArr[i][j] = lcaArr[i-1][lcaArr[i-1][j]];
			}
		}
		
		// Done building farms; wait for queries...
	}
	
	@Override
	public void notifyFJ(int A, int B) {
		// Handle a query by finding the first node that the two target
		// nodes share, then drawing a box from A to that node, and from
		// that node to B. If they share the same node, just draw a box
		// from A to B. This is guaranteed to work because of the way that
		// the tree was built.
		
		// System.out.printf("notifyFJ: %d, %d\n", A, B);
		int lca = findLCA(A, B);
		
		if (lca == A || lca == B) {
			// Special case: Both under the same node
			// Just draw a box from A to B
			addBox(Math.min(farmX[A], farmX[B]),
				   Math.min(farmY[A], farmY[B]),
				   Math.max(farmX[A], farmX[B]),
				   Math.max(farmY[A], farmY[B]));
			return;
		}
		
		// Draw a box from A to meetNode
		int x1 = Math.min(farmX[A], farmX[lca]);
		int x2 = Math.max(farmX[A], farmX[lca]);
		int y1 = Math.min(farmY[A], farmY[lca]);
		int y2 = Math.max(farmY[A], farmY[lca]);
		// Draw a box from lca to B
		int x3 = Math.min(farmX[lca], farmX[B]);
		int x4 = Math.max(farmX[lca], farmX[B]);
		int y3 = Math.min(farmY[lca], farmY[B]);
		int y4 = Math.max(farmY[lca], farmY[B]);
			   
		// Shrink the second box by one width and one height to avoid overlap
		x3 += 1;
		y4 -= 1;
		
		// Add the boxes
		addBox(x1, y1, x2, y2);
		addBox(x3, y3, x4, y4);
	}
	
	public int findLCA(int a, int b) {
  		// First, make the two nodes have the same depth
		int n1 = (depth[a] > depth[b]) ? a : b;
		int n2 = (depth[a] > depth[b]) ? b : a;
		// n1 might need to move up
		int toMove = depth[n1] - depth[n2];
		for (int i = 17; i >= 0; i--) {
			if ((1 << i) <= toMove) {
				n1 = lcaArr[i][n1];
				toMove -= 1 << i;
			}
		}
		
		// Special case: Two nodes on same branch
		if (n1 == n2) return n1;
		// Find LCA
		for (int i = 17; i >= 0; i--) {
			if (lcaArr[i][n1] != lcaArr[i][n2]) {
				n1 = lcaArr[i][n1];
				n2 = lcaArr[i][n2];
			}
		}
		
		return lcaArr[0][n1];
	}
	
	public void buildTree(int node, int yOffset) {
		// Builds all the farms by doing yet another DFS.
		setFarmLocation(node, currX, underCount[node] + yOffset);
		farmX[node] = currX;
		farmY[node] = underCount[node] + yOffset;
		currX++;
		
		for (int neighbor : connections[node]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				// Continue recursion
				buildTree(neighbor, yOffset);
				yOffset += underCount[neighbor];
			}
		}
	}
	
	public void traverseTree() {
		// Fills in the underWhich and underCount arrays.
		// Starts at node 0, and uses DFS to branch out.
		underWhich = new int[numFarms];
		underCount = new int[numFarms];
		depth = new int[numFarms];
		lcaArr = new int[18][numFarms];
		visited = new boolean[numFarms];
		visited[0] = true;
		traverseRec(0, 0);
	}
	
	public int traverseRec(int node, int dep) {
		// Count the # of nodes under this one
		int currCount = 1;
		depth[node] = dep;
		
		// Keep track of the closest node above this one that branches out
		underWhich[node] = currUnder;
		
		// Visit all unvisited neighbors (children of this node)
		int numNeighbors = connections[node].size();
		
		for (int neighbor : connections[node]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				lcaArr[0][neighbor] = node;
				if (numNeighbors > 0) {
					// This one branches out; let children know
					currUnder = node;
				}
				
				// Continue recursion
				currCount += traverseRec(neighbor, dep + 1);
			}
		}
		
		// How many children (including itself) does this node have?
		underCount[node] = currCount;
		return currCount;
	}
}