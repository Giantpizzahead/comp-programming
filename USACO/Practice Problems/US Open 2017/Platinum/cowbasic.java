/*
Solution: Use matrix exponentiation to speed up for loops & addition. Since there can be at max 100 variables, each for
loop will take max O(N^3 * log(N)) time. However, since 100 variables would mean no for loops, the actual upper bound
is much lower.

Runtime: O(50 * (50^3 * log(50)) worst case -> O(2500 * log(50))
*/

import java.util.*;
import java.io.*;

public class cowbasic {
    BufferedReader fin;
    StringTokenizer st;
    HashMap<String, Integer> nameToID = new HashMap<>();
    ArrayList<String> finTokens = new ArrayList<>();
    Stack<String> tokens = new Stack<>();
    Stack<Integer> loopRepeats = new Stack<>();
    Stack<Integer[][]> matrices = new Stack<>();
    Integer[][] currMat;
    int numVars = 0;
    boolean isAssignment = false;
    String targetVar;
    final int MOD = 1000000007;

    cowbasic() throws IOException {
        fin = new BufferedReader(new FileReader("cowbasic.in"));
        st = new StringTokenizer(fin.readLine());

        // First pass; just get # of variables / label variables with ID
        String token = "";
        while (!token.equals("RETURN")) {
            token = getNextToken();
            if (token.equals("(") || token.equals(")")) continue;
            else if (token.equals("=")) {
                // Record variable name
                String varName = tokens.pop();
                if (!nameToID.containsKey(varName)) nameToID.put(varName, numVars++);
                isAssignment = true;
            } else tokens.add(token);

            finTokens.add(token);
        }

        // Record returned var
        finTokens.add(getNextToken());

        // System.out.println(nameToID);
        isAssignment = false;
        tokens.clear();
        fin.close();

        // Second pass; actually handle the tokens now
        // Base matrix (last index is the constant 1)
        currMat = new Integer[numVars + 1][numVars + 1];
        for (int i = 0; i < numVars + 1; i++) Arrays.fill(currMat[i], 0);
        currMat[numVars][numVars] = 1;

        int answer = -1;
        for (int i = 0; i < finTokens.size(); i++) {
            token = finTokens.get(i);
            // System.out.print(token + " ");
            tokens.add(token);
            switch (token) {
                case "{":
                    startForLoop();
                    break;
                case "}":
                    endForLoop();
                    break;
                case ";":
                    assignment();
                    break;
                case "RETURN":
                    answer = handleReturn(finTokens.get(++i));
                    break;
                case "=":
                    targetVar = finTokens.get(i - 1);
                    break;
                case "MOO":
                    loopRepeats.add(Integer.parseInt(finTokens.get(i - 1)));
                    break;
            }
        }

        PrintWriter fout = new PrintWriter("cowbasic.out");
        fout.println(answer);
        fout.close();
    }

    void startForLoop() {
        // Save current matrix and start a new one (identity matrix)
        matrices.add(currMat);
        currMat = new Integer[numVars + 1][numVars + 1];
        for (int i = 0; i < numVars + 1; i++) Arrays.fill(currMat[i], 0);
        for (int i = 0; i < numVars + 1; i++) currMat[i][i] = 1;
    }

    void endForLoop() {
        // Do matrix exponentiation on outer matrix
        int numRepeats = loopRepeats.pop();
        Integer[][] outerMat = matrices.pop();

//        System.out.println("\nOuter mat:");
//        printMatrix(outerMat);

        while (numRepeats > 0) {
            if (numRepeats % 2 == 1) outerMat = multMatrices(outerMat, currMat);
            numRepeats /= 2;
            currMat = multMatrices(currMat, currMat);
        }

        // Set new current matrix
        currMat = outerMat;

//        System.out.println("After mult:");
//        printMatrix(currMat);
//        System.out.println();
    }

    void assignment() {
        tokens.pop();

        // Update transition matrix based on assignments
        int targetID = nameToID.get(targetVar);
        int[] newMat = new int[numVars + 1];

        String token = tokens.pop();
        while (!token.equals("=")) {
            if (!token.equals("+")) {
                if (!nameToID.containsKey(token)) {
                    // Numeric literal
                    newMat[numVars] += Integer.parseInt(token);
                } else {
                    // Variable; add that var's matrix to this one
                    int currID = nameToID.get(token);
                    for (int i = 0; i < numVars + 1; i++) {
                        newMat[i] = (newMat[i] + currMat[i][currID]) % MOD;
                    }
                }
            }

            token = tokens.pop();
        }

        // Replace curr matrix with new one
        // System.out.println("Updating " + targetID);
        // System.out.println(Arrays.toString(newMat));
        for (int i = 0; i < numVars + 1; i++) currMat[i][targetID] = newMat[i];
    }

    int handleReturn(String varToReturn) {
        return currMat[numVars][nameToID.get(varToReturn)];
    }

    Integer[][] multMatrices(Integer[][] A, Integer[][] B) {
        assert (A[0].length == B.length);
        Integer[][] R = new Integer[A.length][B[0].length];
        for (int i = 0; i < A.length; i++) Arrays.fill(R[i], 0);

        for (int i = 0; i < R.length; i++) {
            for (int j = 0; j < R[0].length; j++) {
                for (int k = 0; k < B.length; k++) {
                    R[i][j] = (int) ((R[i][j] + ((long) A[i][k] * B[k][j])) % MOD);
                }
            }
        }
        return R;
    }

    void printMatrix(Integer[][] mat) {
        for (Integer[] integers : mat) System.out.println(Arrays.toString(integers));
    }

    String getNextToken() throws IOException {
        while (!st.hasMoreTokens()) {
            if (isAssignment) {
                finTokens.add(";");  // For easier processing
                isAssignment = false;
            }
            st = new StringTokenizer(fin.readLine());
        }
        return st.nextToken();
    }

    public static void main(String[] args) throws IOException {
        new cowbasic();
    }
}