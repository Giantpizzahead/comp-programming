/*
ID: sunnyky1
LANG: JAVA
TASK: transform
*/

import java.util.*;
import java.io.*;

public class transform {
	static int[][] original, transformed;
	static int N;

	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("transform.in"));
		N = Integer.parseInt(fin.readLine());
		String line;
		
		original = new int[N][N];
		for (int y = 0; y < N; y++) {
			line = fin.readLine();
			for (int x = 0; x < N; x++) {
				original[y][x] = (line.charAt(x) == '@') ? 1 : 0;
			}
		}
		transformed = new int[N][N];
		for (int y = 0; y < N; y++) {
			line = fin.readLine();
			for (int x = 0; x < N; x++) {
				transformed[y][x] = (line.charAt(x) == '@') ? 1 : 0;
			}
		}
		
		fin.close();
		
		int answer = testTransformations();
		PrintWriter fout = new PrintWriter("transform.out");
		fout.println(answer);
		fout.close();
	}
	
	static int testTransformations() {
		// Test 90 degree rotation
		int[][] rotated = rotate90(original);
		if (Arrays.deepEquals(rotated, transformed)) return 1;
		// Test 180 degree rotation
		rotated = rotate90(rotated);
		if (Arrays.deepEquals(rotated, transformed)) return 2;
		// Test 270 degree rotation
		rotated = rotate90(rotated);
		if (Arrays.deepEquals(rotated, transformed)) return 3;
		// Test reflection
		rotated = reflect(original);
		if (Arrays.deepEquals(rotated, transformed)) return 4;
		// Test reflection + some rotation
		for (int i = 0; i < 3; i++) {
			rotated = rotate90(rotated);
			if (Arrays.deepEquals(rotated, transformed)) return 5;
		}
		// Test no change
		if (Arrays.deepEquals(original, transformed)) return 6;
		// Invalid
		return 7;
	}
	
	// Rotates the given square array by 90 degrees.
	static int[][] rotate90(int[][] array) {
		int[][] rotated = new int[N][N];
		int newX, newY;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				newX = N - 1 - y;
				newY = x;
				rotated[newY][newX] = array[y][x];
			}
		}
		return rotated;
	}
	
	// Reflects the given square array horizontally.
	static int[][] reflect(int[][] array) {
		int[][] reflected = new int[N][N];
		int newX;
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				newX = N - 1 - x;
				reflected[y][newX] = array[y][x];
			}
		}
		return reflected;
	}

}
