/*
ID: sunnyky1
LANG: JAVA
TASK: heritage

Solution: The in-order traversal of the tree tells you which nodes are to the left and
right of a given node; the pre-order traversal tells you which nodes are the first to
appear on that side. Using this, you can use a sort of divide and conquer to generate
the original tree.
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class heritage {
    int N;
    char[] iToChar;
    int[] charToI, inOrder, preOrder, valToInOrderLoc;
    Node root;

    heritage(BufferedReader in, PrintWriter out) throws IOException {
        String inOrderStr = in.readLine();
        String preOrderStr = in.readLine();
        N = inOrderStr.length();
        charToI = new int[26];
        iToChar = new char[26];
        for (int i = 0; i < N; i++) {
            char c = inOrderStr.charAt(i);
            charToI[c - 'A'] = i;
            iToChar[i] = c;
        }
        inOrder = new int[N];
        preOrder = new int[N];
        valToInOrderLoc = new int[N];
        for (int i = 0; i < N; i++) {
            inOrder[i] = charToI[inOrderStr.charAt(i) - 'A'];
            preOrder[i] = charToI[preOrderStr.charAt(i) - 'A'];
            valToInOrderLoc[inOrder[i]] = i;
        }

        root = genTree(0, N-1, 0);
        getPostOrder(root);
        for (int i : postOrder) out.print(iToChar[i]);
        out.println();
    }

    Queue<Integer> postOrder = new LinkedList<>();
    void getPostOrder(Node node) {
        if (node == null) return;
        getPostOrder(node.left);
        getPostOrder(node.right);
        postOrder.add(node.val);
    }

    Node genTree(int l, int r, int pre) {
        if (l > r) return null;
        int inOrderLoc = valToInOrderLoc[preOrder[pre]];
        // Is this node meant for this subtree?
        if (inOrderLoc < l || inOrderLoc > r) return genTree(l, r, pre + 1);
        Node node = new Node(preOrder[pre]);
        int splitLoc = valToInOrderLoc[node.val];
        node.left = genTree(l, splitLoc - 1, pre + 1);
        node.right = genTree(splitLoc + 1, r, pre + 1);
        return node;
    }

    static class Node {
        int val;
        Node left, right;
        Node(int val) {
            this.val = val;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("heritage.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("heritage.out")));
        new heritage(in, out);
        in.close();
        out.close();
    }
}
