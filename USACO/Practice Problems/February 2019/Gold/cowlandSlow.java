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

public class cowlandSlow {
	ArrayList<Integer>[] graph;
	int[] enjoymentValues;
	int[][] precalculatedEnjoyment;
	Query[] queries;
	int numAttractions, numQueries;
	
	public cowlandSlow() throws IOException {
		getInput();
		simulate();
	}
	
	void usePrecalculated() throws IOException {
		// Go from every node, and calculate all the enjoyment values
		precalculatedEnjoyment = new int[numAttractions][numAttractions];
		for (int i = 0; i < numAttractions; i++) {
			routeFillPrecalc(i);
		}
		
		// Do all the queries using the precalculated values
		StringBuilder output = new StringBuilder();
		for (Query query : queries) {
			if (query.type == 1) {
				// Update an enjoyment value
				for (int i = 0; i < numAttractions; i++) {
					precalculatedEnjoyment[query.v1][i] ^= enjoymentValues[query.v1];
					if (i != query.v1) precalculatedEnjoyment[i][query.v1] ^= enjoymentValues[query.v1];
					
					precalculatedEnjoyment[query.v1][i] ^= query.v2;
					if (i != query.v1) precalculatedEnjoyment[i][query.v1] ^= query.v2;
				}
				enjoymentValues[query.v1] = query.v2;
			} else {
				// Find route enjoyment
				int enjoyment = precalculatedEnjoyment[query.v1][query.v2];
				output.append(enjoyment + "\n");
				// System.out.println(enjoyment);
			}
		}
		
		PrintWriter fout = new PrintWriter("cowland.out");
		fout.print(output);
		fout.close();
	}
	
	/**
	 * Simulates the route from n1 to n2. Fills the precalculated array along the way.
	 * Uses BFS.
	 */
	void routeFillPrecalc(int n) {
		Queue<State> toEval = new LinkedList<State>();
		toEval.add(new State(n, 0));
		boolean[] visited = new boolean[numAttractions];
		visited[n] = true;
		
		// Main BFS loop
		State c;
		int enjoyment;
		while (!toEval.isEmpty()) {
			c = toEval.poll();
			
			// Add the current node's enjoyment value
			enjoyment = c.e ^ enjoymentValues[c.n];
			
			// Add enjoyment value to the precalculated array
			precalculatedEnjoyment[n][c.n] = enjoyment;
			
			// Spread out to all unvisited neighbors
			for (int neighbor : graph[c.n]) {
				if (!visited[neighbor]) {
					toEval.add(new State(neighbor, enjoyment));
					visited[neighbor] = true;
				}
			}
		}
		
		// No path found...?
	}
	
	/**
	 * Solves the problem by simulating all the queries. Works, but is too slow.
	 * Use this to test another program's answers.
	 */
	void simulate() throws IOException {
		StringBuilder output = new StringBuilder();
		
		// Handle each query
		for (Query query : queries) {
			if (query.type == 1) {
				// Update an enjoyment value
				enjoymentValues[query.v1] = query.v2;
			} else {
				// Find route enjoyment
				int enjoyment = simulateRoute(query.v1, query.v2);
				output.append(enjoyment + "\n");
				// System.out.println(enjoyment);
			}
		}
		
		PrintWriter fout = new PrintWriter("cowland.out");
		fout.print(output);
		fout.close();
	}
	
	/**
	 * Simulates the route from n1 to n2. Finds the enjoyment value along the way.
	 * Uses BFS. (Trying DFS to see if it passes more cases)
	 */
	int simulateRoute(int n1, int n2) {
		Stack<State> toEval = new Stack<State>();
		toEval.add(new State(n1, 0));
		boolean[] visited = new boolean[numAttractions];
		visited[n1] = true;
		
		// Main BFS loop
		State c;
		int enjoyment;
		while (!toEval.isEmpty()) {
			c = toEval.pop();
			
			// Add the current node's enjoyment value
			enjoyment = c.e ^ enjoymentValues[c.n];
			
			// Check if at destination
			if (c.n == n2) {
				// Return the answer
				return enjoyment;
			}
			
			// Spread out to all unvisited neighbors
			for (int neighbor : graph[c.n]) {
				if (!visited[neighbor]) {
					toEval.add(new State(neighbor, enjoyment));
					visited[neighbor] = true;
				}
			}
		}
		
		// No path found...?
		return -1;
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
		new cowlandSlow();
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