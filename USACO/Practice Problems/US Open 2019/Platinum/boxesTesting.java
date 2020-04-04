import java.util.*;

public class boxesTesting {
	
	public static ArrayList<Integer>[] connections;
	public static int[] underWhich, underCount, farmX, farmY;
	public static boolean[] visited;
	public static int numFarms = 0;
	public static int numNotifys = 0;
	public static int currUnder = 0;
	public static int currX = 1;
	
	public static void main(String[] args) {
		testCase2();
	}
	
	public static void testCase1() {
		addRoad(0, 1);
		addRoad(1, 2);
		addRoad(2, 3);
		addRoad(3, 4);
		addRoad(4, 5);
		addRoad(0, 6);
		buildFarms();
		notifyFJ(0, 4);
		notifyFJ(2, 5);
		notifyFJ(5, 6);
		notifyFJ(4, 5);
	}
	
	public static void testCase2() {
		addRoad(0, 2);
		addRoad(1, 0);
		addRoad(4, 2);
		addRoad(2, 5);
		addRoad(3, 6);
		addRoad(3, 0);
		buildFarms();
		notifyFJ(0, 3);
		notifyFJ(5, 6);
		notifyFJ(1, 4);
		notifyFJ(2, 6);
	}
	
	public static void notifyFJ(int A, int B) {
		// Handle a query by finding the first node that the two target
		// nodes share, then drawing a box from A to that node, and from
		// that node to B. If they share the same node, just draw a box
		// from A to B. This is guarenteed to work because of the way that
		// the tree was built.
		
		System.out.printf("notifyFJ: %d, %d\n", A, B);
		HashSet<Integer> underA = new HashSet<Integer>();
		HashSet<Integer> underB = new HashSet<Integer>();
		int currA = underWhich[A];
		int currB = underWhich[B];
		
		if (currA == B || currB == A) {
			// Special case: Both under the same node
			// Just draw a box from A to B
			addBox(Math.min(farmX[A], farmX[B]),
				   Math.min(farmY[A], farmY[B]),
				   Math.max(farmX[A], farmX[B]),
				   Math.max(farmY[A], farmY[B]));
			return;
		}
		
		underA.add(currA);
		underB.add(currB);
		while (!underA.contains(currB) && !underB.contains(currA)) {
			currA = underWhich[currA];
			currB = underWhich[currB];
			if (currA == B || currB == A) {
				// Special case: Both under the same node
				// Just draw a box from A to B
				addBox(Math.min(farmX[A], farmX[B]),
					   Math.min(farmY[A], farmY[B]),
					   Math.max(farmX[A], farmX[B]),
					   Math.max(farmY[A], farmY[B]));
				return;
			}
			underA.add(currA);
			underB.add(currB);
		}
		
		// Find the node where the two first meet up
		int meetNode;
		if (underA.contains(currB)) {
			meetNode = currB;
		} else {
			meetNode = currA;
		}
		System.out.println("Met at " + meetNode);
		
		// Draw a box from A to meetNode
		int x1 = Math.min(farmX[A], farmX[meetNode]);
		int x2 = Math.max(farmX[A], farmX[meetNode]);
		int y1 = Math.min(farmY[A], farmY[meetNode]);
		int y2 = Math.max(farmY[A], farmY[meetNode]);
		// Draw a box from meetNode to B
		int x3 = Math.min(farmX[meetNode], farmX[B]);
		int x4 = Math.max(farmX[meetNode], farmX[B]);
		int y3 = Math.min(farmY[meetNode], farmY[B]);
		int y4 = Math.max(farmY[meetNode], farmY[B]);
			   
		// Shrink the second box by one width and one height to avoid overlap
		x3 += 1;
		y4 -= 1;
		
		// Add the boxes
		addBox(x1, y1, x2, y2);
		addBox(x3, y3, x4, y4);
	}
	
	public static void buildFarms() {
		// Builds all the farms using the method on the drafting paper.
		// Start by traversing the tree, and setting the required values.
		traverseTree();
		
		for (int i = 0; i < numFarms; i++) {
			System.out.print(underWhich[i] + " ");
		}
		System.out.println();
		for (int i = 0; i < numFarms; i++) {
			System.out.print(underCount[i] + " ");
		}
		System.out.println();
		
		// Then, build the farms using the algorithm on the paper
		// Do this by doing another DFS
		visited = new boolean[numFarms];
		visited[0] = true;
		farmX = new int[numFarms];
		farmY = new int[numFarms];
		buildTree(0, 0);
		
		// Done building farms; wait for queries...
	}
	
	public static void buildTree(int node, int yOffset) {
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
	
	public static void traverseTree() {
		// Fills in the underWhich and underCount arrays.
		// Starts at node 0, and uses DFS to branch out.
		underWhich = new int[numFarms];
		underCount = new int[numFarms];
		visited = new boolean[numFarms];
		visited[0] = true;
		traverseRec(0);
	}
	
	public static int traverseRec(int node) {
		// Count the # of nodes under this one
		int currCount = 1;
		
		// Keep track of the closest node above this one that branches out
		underWhich[node] = currUnder;
		
		// Visit all unvisited neighbors (children of this node)
		int numNeighbors = connections[node].size();
		
		for (int neighbor : connections[node]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				if (numNeighbors > 0) {
					// This one branches out; let children know
					currUnder = node;
				}
				
				// Continue recursion
				currCount += traverseRec(neighbor);
			}
		}
		
		// How many children (including itself) does this node have?
		underCount[node] = currCount;
		return currCount;
	}
	
	@SuppressWarnings("unchecked")
	public static void addRoad(int A, int B) {
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
	
	
	
	
	
	// Simulated grader methods
	public static int getN() {
		return 7;
	}
	
	public static int getQ() {
		return 5;
	}
	
	public static void setFarmLocation(int id, int x, int y) {
		System.out.printf("Farm %d placed at (%d, %d)\n", id, x, y);
	}
	
	public static void addBox(int x1, int y1, int x2, int y2) {
		System.out.printf("Box placed with endpoints (%d, %d), (%d, %d)\n", x1, y1, x2, y2);
	}
	
}