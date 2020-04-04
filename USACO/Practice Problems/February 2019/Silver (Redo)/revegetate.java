import java.util.*;
import java.io.*;

public class revegetate {
	
	public static ArrayList<Conn>[] graph;
	public static int[] types;
	public static int numPastures, numCows;

	public static void main(String[] args) throws IOException {
		getInput();
		int numClusters = findClusters();
		PrintWriter fout = new PrintWriter("revegetate.out");
		if (numClusters == -1) {
			// Impossible
			fout.println(0);
		} else {
			// Not impossible
			fout.print(1);
			for (int i = 0; i < numClusters; i++) {
				fout.print(0);
			}
			fout.println();
		}
		fout.close();
	}
	
	public static int findClusters() {
		// True edge = Same type of grass, False edge = Different type
		types = new int[numPastures];
		// If types[i] is 0, then it isn't visited
		int numClusters = 0;
		
		// Find a new cluster to evaluate
		for (int i = 0; i < numPastures; i++) {
			if (types[i] == 0) {
				// New unevaluated cluster; start from there
				numClusters++;
				if (!exploreCluster(i)) {
					// Returned false, therefore it's impossible
					// Return -1
					return -1;
				}
			}
		}
		
		return numClusters;
	}
	
	public static boolean exploreCluster(int startNode) {
		Queue<Integer> toEval = new LinkedList<Integer>();
		
		// Evaluate the new cluster
		toEval.add(startNode);
		types[startNode] = 1;
		
		int curr;
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			
			// Find neighbors
			for (Conn conn : graph[curr]) {
				if (types[conn.node] != 0) {
					// This node's been visited already; check if the connection's impossible
					if (conn.isSame && types[curr] != types[conn.node]) {
						// Impossible
						return false;
					} else if (!conn.isSame && types[curr] == types[conn.node]) {
						// Also impossible
						return false;
					}
				} else {
					// Not yet visited; set appropriate int and add to eval
					if (conn.isSame) {
						types[conn.node] = types[curr]; 
					} else {
						types[conn.node] = 3 - types[curr];
					}
					toEval.add(conn.node);
				}
			}
		}
		
		return true;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	@SuppressWarnings("unchecked")
	public static void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("revegetate.in"));
		String[] line = fin.readLine().split(" ");
		numPastures = Integer.parseInt(line[0]);
		numCows = Integer.parseInt(line[1]);
		
		// Initialize graph
		graph = new ArrayList[numPastures];
		for (int i = 0; i < numPastures; i++) {
			graph[i] = new ArrayList<Conn>();
		}
		
		// Parse all preferences, and record them while parsing
		// A true edge = Same type of grass, A false edge = Different type of grass
		char type;
		int p1, p2;
		for (int i = 0; i < numCows; i++) {
			line = fin.readLine().split(" ");
			type = line[0].charAt(0);
			p1 = Integer.parseInt(line[1]) - 1;
			p2 = Integer.parseInt(line[2]) - 1;
			if (type == 'S') {
				graph[p1].add(new Conn(p2, true));
				graph[p2].add(new Conn(p1, true));
			} else {
				graph[p1].add(new Conn(p2, false));
				graph[p2].add(new Conn(p1, false));
			}
		}
		
		fin.close();
	}
	
	static class Conn {
		int node;
		boolean isSame;
		public Conn(int node, boolean isSame) {
			this.node = node;
			this.isSame = isSame;
		}
	}

}
