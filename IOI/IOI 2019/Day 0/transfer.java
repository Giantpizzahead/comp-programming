import java.util.*;

class transfer {
	int N, maxPow2, maxD;
	int[] bits, bitCount;
	
	int[] get_attachment(int[] source) {
		N = source.length;
		bits = new int[source.length + 1];
		for (int i = 0; i < N; i++) bits[i] = source[i];
		if (N < 64) {
			maxPow2 = 64;
			maxD = 6;
		} else {
			maxPow2 = 256;
			maxD = 8;
		}

		// Add bit to the source = The parity of all the other bits
		bits[N] = getParity(0, N-1);

		bitCount = new int[maxD + 1];
		bitCount[0] = bits[N];
		N++;
		countBits(0, maxPow2 - 1, 1);

		// Make new sequence with attachment
		for (int i = 0; i < maxD + 1; i++) bitCount[i] %= 2;
		System.out.println(Arrays.toString(bitCount));
		return bitCount;
	}

	void countBits(int low, int high, int d) {
		if (low == high) return;
		// Count on left side
		int mid = (low + high) / 2;
		for (int i = low; i <= mid; i++) {
			if (i >= N) break;
			if (bits[i] == 1) bitCount[d]++;
		}
		// Split up
		countBits(low, mid, d + 1);
		countBits(mid + 1, high, d + 1);
	}

	int getParity(int l, int r) {
		int count = 0;
		for (int i = l; i <= r; i++) if (bits[i] == 1) count++;
		return count % 2;
	}
	
	int[] retrieve(int[] data) {
		N = data.length;
		bits = data;
		if (N < 72) {
			maxPow2 = 64;
			maxD = 6;
			N -= 7;
		} else {
			maxPow2 = 256;
			maxD = 8;
			N -= 9;
		}

		// Was the block corrupted?
		int corruptedLoc;
		if (getParity(0, N-1) != bits[N]) {
			// Source corrupted (or that last bit)
			N++;
			bitCount = new int[maxD];
			countBits(0, maxPow2-1, 0);
			corruptedLoc = retrieveCorrupted(0, maxPow2-1, 0);
			N--;
		} else {
			// Original data is fine
			corruptedLoc = -1;
		}

		// Generate source
		int[] source = new int[N];
		for (int i = 0; i < N; i++) {
			if (corruptedLoc == i) source[i] = 1 - bits[i];
			else source[i] = bits[i];
		}
		System.out.println(Arrays.toString(source));
		return source;
	}

	int retrieveCorrupted(int low, int high, int d) {
		if (low == high) return low;  // This bit is corrupted
		int mid = (low + high) / 2;
		// Check for validity
		if (bitCount[d] % 2 == bits[N+d]) {
			// Left wasn't corrupted
			return retrieveCorrupted(mid+1, high, d+1);
		} else {
			// Left corrupted
			return retrieveCorrupted(low, mid, d+1);
		}
	}
	
}
