/**
 * USACO 2019 February Contest (Gold)
 * Problem 1. Cow Land
 * 
 * Why not just simulate it? NQ is a hundred million, which should run in time...
 * I guess we'll try simulating it???
 *
 */

import java.util.*;
import java.io.*;

public class cowland {
	ArrayList<Integer>[] graph;
	int[] enjoymentValues, enjoymentFromRoot, branchNodeToRoot, nodeToRoot;
	Query[] queries;
	int numAttractions, numQueries;
	
	public cowland() throws IOException {
		getInput();
		usePrecalculated();
	}
	
	void usePrecalculated() throws IOException {
		// Go from the root node, and calculate all the enjoyment values
		fillFromRoot();
		
		// Do all the queries using the precalculated values
		StringBuilder output = new StringBuilder();
		for (Query query : queries) {
			if (query.type == 1) {
				// Update an enjoyment value
				enjoymentValues[query.v1] = query.v2;
				fillFromRoot();
			} else {
				// Find route enjoyment
				int overlapNode = findFirstOverlap(query.v1, query.v2);
				int enjoyment = enjoymentFromRoot[query.v1] ^ enjoymentFromRoot[query.v2] ^ enjoymentValues[overlapNode];
				output.append(enjoyment + "\n");
				// System.out.println(enjoyment);
			}
		}
		
		PrintWriter fout = new PrintWriter("cowland.out");
		fout.print(output);
		fout.close();
	}
	
	/**
	 * Simulates the route from the root node to all other nodes.
	 * Fills all the root arrays along the way.
	 * Uses BFS.
	 */
	void fillFromRoot() {
		enjoymentFromRoot = new int[numAttractions];
		branchNodeToRoot = new int[numAttractions];
		nodeToRoot = new int[numAttractions];
		
		Queue<State> toEval = new LinkedList<State>();
		toEval.add(new State(0, 0));
		boolean[] visited = new boolean[numAttractions];
		visited[0] = true;
		
		// Main BFS loop
		State c;
		int enjoyment;
		while (!toEval.isEmpty()) {
			c = toEval.poll();
			
			// Add the current node's enjoyment value
			enjoyment = c.e ^ enjoymentValues[c.n];
			
			// Add enjoyment value to the precalculated array
			enjoymentFromRoot[c.n] = enjoyment;
			
			// Spread out to all unvisited neighbors
			for (int neighbor : graph[c.n]) {
				if (!visited[neighbor]) {
					// Check if this is a branch node
					if (graph[c.n].size() > 2) {
						// Branch node
						branchNodeToRoot[neighbor] = c.n;
						// toEval.add(new State(neighbor, enjoymentValues[c.n]));
					} else {
						branchNodeToRoot[neighbor] = branchNodeToRoot[c.n];
						// toEval.add(new State(neighbor, enjoyment));
					}
					
					toEval.add(new State(neighbor, enjoyment));
					
					nodeToRoot[neighbor] = c.n;
					visited[neighbor] = true;
				}
			}
		}
		
		// No path found...?
	}
	
	/**
	 * Finds the first branch node at which the paths to root from n1 and n2 intersect.
	 */
	int findFirstOverlap(int n1, int n2) {
		if (n1 == n2) return n1;
		
		HashSet<Integer> path1 = new HashSet<Integer>();
		path1.add(n1);
		HashSet<Integer> path2 = new HashSet<Integer>();
		path2.add(n2);
		
		int next1 = n1;
		int next2 = n2;
		
		// This should NOT loop forever, so it should be ok
		while (true) {
			next1 = nodeToRoot[next1];
			next2 = nodeToRoot[next2];
			
			if (next1 == next2) return next1;
			if (path1.contains(next2)) return next2;
			if (path2.contains(next1)) return next1;
			
			path1.add(next1);
			path2.add(next2);
		}
	}
	
	@SuppressWarnings("unchecked")
	void getInput() throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("cowland.in"));
		String[] rawLine = fin.readLine().split(" ");
		numAttractions = Integer.parseInt(rawLine[0]);
		numQueries = Integer.parseInt(rawLine[1]);
		
		// Parse attraction enjoyment values
		rawLine = fin.readLine().split(" ");
		enjoymentValues = new int[numAttractions];
		for (int i = 0; i < rawLine.length; i++) {
			enjoymentValues[i] = Integer.parseInt(rawLine[i]);
		}
		
		// Parse all pathways
		graph = new ArrayList[numAttractions];
		for (int i = 0; i < numAttractions; i++) {
			graph[i] = new ArrayList<Integer>();
		}
		
		int[] line = new int[2];
		for (int i = 0; i < numAttractions - 1; i++) {
			rawLine = fin.readLine().split(" ");
			line[0] = Integer.parseInt(rawLine[0]) - 1;
			line[1] = Integer.parseInt(rawLine[1]) - 1;
			graph[line[0]].add(line[1]);
			graph[line[1]].add(line[0]);
		}
		
		// Parse all queries
		queries = new Query[numQueries];
		line = new int[3];
		for (int i = 0; i < numQueries; i++) {
			rawLine = fin.readLine().split(" ");
			line[0] = Integer.parseInt(rawLine[0]);
			line[1] = Integer.parseInt(rawLine[1]) - 1;
			line[2] = Integer.parseInt(rawLine[2]);
			if (line[0] == 2) {
				line[2]--;
			}
			queries[i] = new Query(line[0], line[1], line[2]);
		}
		
		fin.close();
	}

	public static void main(String[] args) throws IOException {
		// Bitwise XOR is ^
		new cowland();
	}
	
	class Query {
		int type, v1, v2;
		
		public Query(int type, int v1, int v2) {
			this.type = type;
			this.v1 = v1;
			this.v2 = v2;
		}
	}
	
	class State {
		int n, e;
		
		public State(int n, int e) {
			this.n = n;
			this.e = e;
		}
	}

}