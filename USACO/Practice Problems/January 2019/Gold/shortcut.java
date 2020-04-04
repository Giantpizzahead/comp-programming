import java.util.*;
import java.io.*;

public class shortcut {
	
	public static HashMap<Integer, ArrayList<FieldCost>> trails;
	public static int[] numCows, distances, from;
	public static int numFields, numTrails, shortcutDist;
	public static Stack<Integer> fieldsToEval;
	public static int INF = 999999999;
	public static boolean debug = false;

	public static void main(String[] args) throws IOException {
		getInput();
		dijkstraFromBarn();
		if (debug) {
			for (int i = 0; i < numFields; i++) {
				System.out.print(distances[i] + " ");
			}
			System.out.println();
			for (int i = 0; i < numFields; i++) {
				System.out.print(from[i] + " ");
			}
			System.out.println();
		}
		long maxDecrease = tryEachShortcut();
		if (debug) {
			System.out.println(maxDecrease);
		} else {
			outputToFile(maxDecrease);
		}
	}
	
	public static void outputToFile(long maxDecrease) throws IOException {
		FileWriter fout = new FileWriter("shortcut.out");
		fout.write(Long.toString(maxDecrease));
		fout.close();
	}
	
	public static long tryEachShortcut() {
		// Tries each shortcut, and sees how much it would decrease the distance by.
		// Saves the highest decrease amount, and returns it.
		long maxDecrease = 0;
		long currDecrease;
		int curr;
		
		while (!fieldsToEval.isEmpty()) {
			if (debug) {
				for (int i = 0; i < numFields; i++) {
					System.out.print(numCows[i] + " ");
				}
				System.out.println();
			}
			
			curr = fieldsToEval.pop();
			// Find decrease in total travel time if shortcut placed on curr
			currDecrease = (long) numCows[curr] * (long) (distances[curr] - shortcutDist);
			
			if (debug) {
				System.out.println("Shortcut on " + (curr+1) + " results in decrease of " + currDecrease);
			}
			
			maxDecrease = Math.max(maxDecrease, currDecrease);
			
			// Move cows to the next field that they'd go to
			numCows[from[curr]] += numCows[curr];
			numCows[curr] = 0;
		}
		
		return maxDecrease;
	}
	
	public static void dijkstraFromBarn() {
		// Perform Dijkstra's algorithm from the barn to get the distance to every field.
		// Use a priority queue.
		PriorityQueue<FieldCost> toEval = new PriorityQueue<FieldCost>(11, new FieldCostComparator());
		HashSet<Integer> visited = new HashSet<Integer>();
		fieldsToEval = new Stack<Integer>();
		// Initialize arrays
		distances = new int[numFields];
		from = new int[numFields];
		for (int i = 0; i < numFields; i++) {
			distances[i] = INF;
			from[i] = -1;
		}
		distances[0] = 0;
		from[0] = 0;
		toEval.add(new FieldCost(0, 0));
		FieldCost curr;
		int newDist;
		
		// Run Dijkstra's algorithm
		while (!toEval.isEmpty()) {
			curr = toEval.poll();
			
			if (visited.contains(curr.f)) {
				continue;
			}
			
			if (debug) {
				System.out.println("Dijkstra: Field " + (curr.f+1) + " Distance " + curr.t);
			}
			
			// Add field to stack for evaluation later, but don't add the barn
			if (curr.f != 0) {
				fieldsToEval.add(curr.f);
			}
			
			// Find curr's neighbors
			for (FieldCost neighbor : trails.get(curr.f)) {
				// If neighbor not in visited, change distance of neighbor to minimum distance possible
				// If new minimum distance is found, readd the neighbor to the priority queue
				if (!visited.contains(neighbor.f)) {
					newDist = curr.t + neighbor.t;
					if (distances[neighbor.f] > newDist || (distances[neighbor.f] == newDist && curr.f < from[neighbor.f])) {
						distances[neighbor.f] = newDist;
						from[neighbor.f] = curr.f;
						toEval.add(new FieldCost(neighbor.f, newDist));
					}
				}
			}
			
			// Add current field to visited
			visited.add(curr.f);
		}
	}
	
	public static void getInput() throws IOException {
		BufferedReader s = new BufferedReader(new FileReader("shortcut.in"));
		String[] line = s.readLine().split(" ");
		numFields = Integer.parseInt(line[0]);
		numTrails = Integer.parseInt(line[1]);
		shortcutDist = Integer.parseInt(line[2]);
		
		// Fill numCows array
		numCows = new int[numFields];
		line = s.readLine().split(" ");
		for (int i = 0; i < numFields; i++) {
			numCows[i] = Integer.parseInt(line[i]);
		}
		
		// Put trails into the trail HashMap
		// -1 to account for zero-indexing
		trails = new HashMap<Integer, ArrayList<FieldCost>>();
		int c1, c2, t;
		for (int i = 0; i < numTrails; i++) {
			line = s.readLine().split(" ");
			c1 = Integer.parseInt(line[0]) - 1;
			c2 = Integer.parseInt(line[1]) - 1;
			t = Integer.parseInt(line[2]);
			if (!trails.containsKey(c1)) {
				trails.put(c1, new ArrayList<FieldCost>());
			}
			if (!trails.containsKey(c2)) {
				trails.put(c2, new ArrayList<FieldCost>());
			}
			trails.get(c1).add(new FieldCost(c2, t));
			trails.get(c2).add(new FieldCost(c1, t));
		}
		
		s.close();
	}
	
	static class FieldCost {
		int f, t;
		public FieldCost(int f, int t) {
			this.f = f;
			this.t = t;
		}
	}
	
	static class FieldCostComparator implements Comparator<FieldCost> {

		@Override
		public int compare(FieldCost t1, FieldCost t2) {
			// Shortest dist should go first; if that ties, smallest index should go first
			if (t1.t > t2.t) {
				return 1;
			} else if (t1.t < t2.t) {
				return -1;
			} else if (t1.f > t2.f) {
				return 1;
			} else {
				return -1;
			}
		}
		
	}

}
