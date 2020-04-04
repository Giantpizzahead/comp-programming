import java.math.BigInteger;
import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class censor {
    final int ALPHABET_SIZE = 29;
    final long MOD = 9283381437989731L;
    int N, S, H;
    String str;
    // Simulates a linked list
    int[] nextChar;
    long[] alphabetPow;

    HashSet<Long>[] wordHashes;
    long[][] currHashes;
    Integer[] iToHashLength;
    String[] words;

    censor(BufferedReader in, PrintWriter out) throws IOException {
        // System.out.println(hashToString(hash("potatoes")));
        str = "|" + in.readLine();
        S = str.length();
        nextChar = new int[S];
        for (int i = 0; i < S; i++) nextChar[i] = i+1;

        alphabetPow = new long[S];
        alphabetPow[0] = 1;
        for (int i = 1; i < S; i++) alphabetPow[i] = alphabetPow[i-1] * ALPHABET_SIZE % MOD;

        N = Integer.parseInt(in.readLine());
        TreeSet<Integer> neededHashLengths = new TreeSet<>();
        words = new String[N];
        for (int i = 0; i < N; i++) {
            words[i] = in.readLine();
            neededHashLengths.add(words[i].length());
        }
        H = neededHashLengths.size();
        iToHashLength = neededHashLengths.toArray(new Integer[0]);

        // Make hashes for all codewords
        wordHashes = new HashSet[H];
        for (int i = 0; i < H; i++) wordHashes[i] = new HashSet<>(2);
        for (int i = 0; i < N; i++) {
            int targetI = Arrays.binarySearch(iToHashLength, words[i].length());
            wordHashes[targetI].add(hash(words[i]));
        }

        // Now, go through the string, deleting all censored words
        // Note: currHashes is offset by 1 to make implementation easier
        int[] prevLocs = new int[S + 1];
        prevLocs[0] = -1;
        currHashes = new long[S][H];
        int currLength = 0;
        outerLoop:
        for (int i = 0; i < S; i = nextChar[i]) {
            currLength++;
            prevLocs[currLength] = i;
            // System.out.println("Char " + i);
            // System.out.println("Length " + currLength);

            // Update hashes
            for (int j = 0; j < H; j++) {
                if (currLength == 1) currHashes[i][j] = 0;
                else currHashes[i][j] = currHashes[prevLocs[currLength - 1]][j];
                if (currLength > iToHashLength[j]) {
                    // Delete last character of this hash
                    long toRemove = alphabetPow[iToHashLength[j] - 1] * charVal(str.charAt(prevLocs[currLength - iToHashLength[j]]));
                    // System.out.println("removing " + str.charAt(prevLocs[currLength - iToHashLength[j]]));
                    currHashes[i][j] = (currHashes[i][j] - toRemove) % MOD;
                    if (currHashes[i][j] < 0) currHashes[i][j] += MOD;
                }
                // Multiply previous chars / add this character to the hash
                currHashes[i][j] = currHashes[i][j] * ALPHABET_SIZE + charVal(str.charAt(i));
                currHashes[i][j] %= MOD;

                // Check if any hashes collide
                if (wordHashes[j].contains(currHashes[i][j])) {
                    // System.out.println("censored!");
                    // Censored word found; adjust linked list & go back to before this word
                    currLength -= iToHashLength[j];
                    nextChar[prevLocs[currLength]] = nextChar[i];
                    i = prevLocs[currLength];
                    // Restart the process
                    continue outerLoop;
                }
                // System.out.println(hashToString(currHashes[i][j]));
            }
        }
        // System.out.println(Arrays.toString(nextChar));

        int c = 0;
        while (c < S) {
            if (c != 0) out.print(str.charAt(c));
            c = nextChar[c];
        }
        out.println();
    }

    int charVal(char c) {
        return 1 + c - 'a';
    }

    // Note: Only works if hash has not yet been modded!
    String hashToString(long hash) {
        StringBuilder sb = new StringBuilder();
        while (hash != 0) {
            sb.append((char) (hash % ALPHABET_SIZE - 1 + 'a'));
            hash /= ALPHABET_SIZE;
        }
        return sb.reverse().toString();
    }

    long hash(String s) {
        long currHash = 0;
        for (int i = 0; i < s.length(); i++) {
            currHash = currHash * ALPHABET_SIZE + charVal(s.charAt(i));
            currHash %= MOD;
        }
        return currHash;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("censor.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("censor.out")));
        new censor(in, out);
        in.close();
        out.close();
    }
}
