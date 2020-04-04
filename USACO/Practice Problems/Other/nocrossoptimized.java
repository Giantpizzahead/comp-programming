import java.util.*;
import java.io.*;

public class nocrossoptimized {
	
	public static int[] leftFields, rightFields;
	// indexesToCheck maps a breed value to the rightFields indexes that need to be checked.
	// It DOES NOT map the left index value to the right one! It maps the left VALUE!
	public static ArrayList<ArrayList<Integer>> indexesToCheck;
	public static Deque<DPState> dpStates;
	public static HashSet<Integer> newXs;
	public static int numBreeds;
	public static int maxConns;
	public static boolean debug = false;

	public static void main(String[] args) throws IOException {
		getInput();
		if (debug) {
			System.out.print("leftFields: ");
			printArray(leftFields);
			System.out.print("rightFields: ");
			printArray(rightFields);
			for (int i = 0; i < numBreeds; i++) {
				System.out.println("For value " + i + ": ");
				for (int j : indexesToCheck.get(i)) {
					System.out.print(j + " ");
				}
				System.out.println();
			}
		}
		fillDPTable();
		if (debug) {
			System.out.println(maxConns);
		}
		FileWriter fout = new FileWriter("nocross.out");
		fout.write(maxConns + "\n");
		fout.close();
	}
	
	public static void printArray(int[] arr) {
		String output = "";
		output += "[";
		for (int item : arr) {
			output += item + ", ";
		}
		output = output.substring(0, output.length() - 2) + "]";
		System.out.println(output);
	}
	
	public static void fillDPTable() {
		newXs = new HashSet<Integer>();
		dpStates = new LinkedList<DPState>();
		dpStates.add(new DPState(0, 0, 0));
		int max, newMax;
		for (int l = 0; l < numBreeds; l++) {
			if (debug) {
				System.out.println("On left node " + l);
			}
			max = 0;
			newXs.clear();
			for (int r : indexesToCheck.get(leftFields[l])) {
				if (debug) {
					System.out.println("Checking index " + r + " with value " + rightFields[r]);
				}
				if (l-1 < 0 || r-1 < 0) {
					newMax = 1;
				} else {
					newMax = findClosestDPState(l-1, r-1) + 1;
				}
				if (newMax > max) {
					dpStates.add(new DPState(l, r, newMax));
					max = newMax;
					newXs.add(r);
					if (debug) {
						System.out.println("Adding new dpState " + l + " " + r + " " + newMax);
					}
				}
				maxConns = Math.max(maxConns, newMax);
			}
			if (l > 1) {
				transferRow(l - 2);
			}
			if (l > 1) {
				deleteRow(l - 2);
			}
		}
	}
	
	public static int findClosestDPState(int l, int r) {
		// Finds the closest DPState that is at least 1 to the left and 1 above the specified location.
		// Will only search in one row. Goes through a deque, meaning it needs 17 operations max.
		// EDIT: Now finds the highest DPState that is at least 1 to the left and 1 above the specified location.
		if (debug) {
			System.out.println("Finding closest DPState from " + l + " " + r);
		}
		Stack<DPState> dpStack = new Stack<DPState>();
		DPState curr = dpStates.pollLast();
		dpStack.add(curr);
		while (curr.l > l || curr.r > r) {
			if (debug) {
				System.out.println("Searching l " + curr.l + " r " + curr.r + " cw " + curr.cw);
			}
			curr = dpStates.pollLast();
			if (curr == null) {
				break;
			}
			dpStack.add(curr);
		}
		int numCrosswalks = 0;
		while (curr != null && curr.l == l) {
			if (debug) {
				System.out.println("Evaluating l " + curr.l + " r " + curr.r + " cw " + curr.cw);
			}
			numCrosswalks = Math.max(numCrosswalks, curr.cw);
			curr = dpStates.pollLast();
			dpStack.add(curr);
		}
		
		// Add everything back from the stack into the deque
		while (!dpStack.isEmpty()) {
			dpStates.add(dpStack.pop());
		}
		if (debug) {
			System.out.println(numCrosswalks);
		}
		return numCrosswalks;
	}
	
	public static void insertDPState(DPState state) {
		// Inserts a DPState to where it's supposed to be.
		Stack<DPState> dpStack = new Stack<DPState>();
		DPState curr = dpStates.pollLast();
		dpStack.add(curr);
		while (curr.l > state.l || curr.r > state.r) {
			curr = dpStates.pollLast();
			if (curr == null) {
				break;
			}
			dpStack.add(curr);
		}
		// Add the new state to the deque
		/*
		if (curr != null) {
			dpStates.add(dpStack.pop());
		}
		*/
		dpStates.add(state);
		
		// Insert everything back from the stack into the deque
		while (!dpStack.isEmpty()) {
			dpStates.add(dpStack.pop());
		}
	}
	
	public static void transferRow(int l) {
		// Transfers a row to a new row in order to preserve any missed DPStates.
		Stack<DPState> dpStack = new Stack<DPState>();
		if (debug) {
			System.out.println("Transferring row " + l);
		}
		DPState curr = dpStates.poll();
		dpStack.add(curr);
		while (curr != null && curr.l == l) {
			if (!newXs.contains(curr.r)) {
				if (debug) {
					System.out.println("Transferred Left " + (curr.l+1) + " right " + curr.r + " cw " + curr.cw);
				}
				insertDPState(new DPState(curr.l+1, curr.r, curr.cw));
			}
			curr = dpStates.poll();
		}
		
		// Insert everything back from the stack into the deque
		while (!dpStack.isEmpty()) {
			dpStates.add(dpStack.pop());
		}
	}
	
	public static void deleteRow(int l) {
		// Deletes an unneeded row to save memory space.
		if (debug) {
			System.out.println("Deleting row " + l);
		}
		DPState curr = dpStates.poll();
		while (curr != null && curr.l == l) {
			if (debug) {
				// System.out.println("Left " + curr.l + " right " + curr.r + " cw " + curr.cw);
			}
			curr = dpStates.poll();
		}
		dpStates.addFirst(curr);
	}
	
	public static void getInput() throws IOException {
		BufferedReader s = new BufferedReader(new FileReader("nocross.in"));
		numBreeds = Integer.parseInt(s.readLine());
		leftFields = new int[numBreeds];
		rightFields = new int[numBreeds];
		for (int i = 0; i < numBreeds; i++) {
			leftFields[i] = Integer.parseInt(s.readLine()) - 1;
		}
		// While parsing right fields, make array linking breed type to index in right fields
		indexesToCheck = new ArrayList<ArrayList<Integer>>();
		for (int i = 0; i < numBreeds; i++) {
			indexesToCheck.add(new ArrayList<Integer>());
		}
		for (int i = 0; i < numBreeds; i++) {
			rightFields[i] = Integer.parseInt(s.readLine()) - 1;
			for (int j = Math.max(0, rightFields[i] - 4); j < Math.min(numBreeds, rightFields[i] + 5); j++) {
				indexesToCheck.get(j).add(i);
			}
		}
		// Sort all the indexes to be checked
		for (int i = 0; i < numBreeds; i++) {
			Collections.sort(indexesToCheck.get(i));
		}
		s.close();
	}

	static class DPState {
		int l, r, cw;
		public DPState (int l, int r, int cw) {
			this.l = l;
			this.r = r;
			this.cw = cw;
		}
	}
	
}
