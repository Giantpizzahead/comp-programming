/*
Solution: The problem deduces to finding the (#LISs - K)th longest increasing subsequence. Make a
BBST that can calculate the sum of all #LDSs in nodes with arr value > a certain value, and insert
values. Entries will look like (i, arr[i], #LDSs).

To make the problem easier, find the # of longest DECREASING subsequences containing each array
element. Iterate from back to front. To handle a new element:
Query BIT for correct LDS BBST to check at that element (check arr value). In the matching BBST,
find # of LDSs in total for nodes with arr[i] > arr[currVal]. Then, insert the element into /
create next BBST at the right LDS size, and increment BIT from 0...currVal by 1.

To generate the right LIS at the end, start from the highest length BBST made. Iterate through
the elements in DECREASING order, summing up the #LDSs found. Stop once this sum > K. Then, add
the current node's value to a HashSet of values in the desired LIS. Finally, recurse on the next
BBST, finding the (K-prevSum)th LIS. Only sum the current value if it's i value > last i value!

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class itout {
    int N, maxLDSLen;
    long K;
    int[] cows;
    final int INF = 987654321;
    HashSet<Integer> cowsInLIS;
    AVLTree[] avlTrees;

    itout() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("itout.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Long.parseLong(st.nextToken());
        cows = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) {
            cows[i] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        /*
        AVLTree avl = new AVLTree();
        avl.add(1, 1, 100);
        avl.add(4, 4, 50);
        avl.add(6, 6, 25);
        avl.add(3, 3, 20);
        avl.add(8, 8, 15);
        avl.add(9, 9, 10);
        for (int i = 0; i < 10; i++) System.out.println(avl.query(i));
        avl.traverse(avl.root);
         */

        findNumLDSs();
        // System.out.println(Arrays.toString(avlTrees));

        // Find requested LIS
        cowsInLIS = new HashSet<>(maxLDSLen + 1);
        findLIS(maxLDSLen, -1, K);

        // System.out.println(cowsInLIS);

        // Generate printout
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("itout.out")));
        fout.println(N - maxLDSLen);
        for (int i = 1; i <= N; i++) {
            if (!cowsInLIS.contains(i)) fout.println(i);
        }
        fout.close();
    }

    void findLIS(int currLDSLen, int lastI, long currK) {
        if (currLDSLen == 0) return;
        Triple result = avlTrees[currLDSLen].nextLISVal(avlTrees[currLDSLen].root, lastI, currK);
        cowsInLIS.add(result.val);
        findLIS(currLDSLen - 1, result.i, result.currK);
    }

    void findNumLDSs() {
        TreeSet<Pair> maxLDSTree = new TreeSet<>(Comparator.comparingInt(x -> x.val));
        // Contains a separate tree for each LDS length
        avlTrees = new AVLTree[N + 1];
        avlTrees[0] = new AVLTree();
        avlTrees[0].add(INF, INF, 1);

        // Iterate through cows in decreasing order
        int currMaxLen;
        long currNumLDSs;
        maxLDSLen = 0;
        for (int i = N-1; i >= 0; i--) {
            // Generate next LDS
            Pair higher = maxLDSTree.higher(new Pair(cows[i], 0));
            currMaxLen = (higher != null) ? higher.LDSLen : 0;
            // System.out.println(currMaxLen + " " + i);
            currNumLDSs = avlTrees[currMaxLen].query(cows[i]);
            if (avlTrees[currMaxLen + 1] == null) avlTrees[currMaxLen + 1] = new AVLTree();
            avlTrees[currMaxLen + 1].add(i, cows[i], currNumLDSs);

            // Update max LDS for elements smaller than a certain number
            Pair currPair = new Pair(cows[i], currMaxLen + 1);
            maxLDSTree.add(currPair);
            // Remove any outdated pairs with smaller values (LDSLen same or less)
            Pair lower = maxLDSTree.lower(currPair);
            while (lower != null && lower.LDSLen <= currPair.LDSLen) {
                maxLDSTree.remove(lower);
                lower = maxLDSTree.lower(currPair);
            }

            maxLDSLen = Math.max(currMaxLen + 1, maxLDSLen);
        }
    }

    public static void main(String[] args) throws IOException {
        new itout();
    }
}

class Triple {
    int i, val;
    long currK;
    Triple(int i, int val, long currK) {
        this.i = i;
        this.val = val;
        this.currK = currK;
    }
}

class Pair {
    int val, LDSLen;
    Pair(int val, int LDSLen) {
        this.val = val;
        this.LDSLen = LDSLen;
    }
}

class BIT {
    int size;
    int[] v;

    BIT(int size) {
        this.size = size;
        v = new int[size + 1];
    }

    // Increments from [1, end].
    void increment(int end) {
        update(1, 1);
        update(end + 1, -1);
    }

    void update(int i, int val) {
        while (i <= size) {
            v[i] += val;
            i += Integer.lowestOneBit(i);
        }
    }

    int query(int index) {
        int result = 0;
        while (index != 0) {
            result += v[index];
            index -= Integer.lowestOneBit(index);
        }
        return result;
    }
}

class AVLTree {
    int size;
    Node root;
    final long MAX_VAL = Long.MAX_VALUE / 3 - 1;

    class Node {
        int i, val, height, bf;
        long numLDSs, sumSubtreeLDSs;
        Node left, right;

        Node(int i, int val, long numLDSs) {
            this.i = i;
            this.val = val;
            this.numLDSs = numLDSs;
            height = 0;
            bf = 0;
            sumSubtreeLDSs = numLDSs;
        }

        void update() {
            int lh, rh;
            long ls, rs;
            if (left != null) {
                lh = left.height;
                ls = left.sumSubtreeLDSs;
            } else {
                lh = -1;
                ls = 0;
            }
            if (right != null) {
                rh = right.height;
                rs = right.sumSubtreeLDSs;
            } else {
                rh = -1;
                rs = 0;
            }
            height = Math.max(lh, rh) + 1;
            bf = rh - lh;
            sumSubtreeLDSs = Math.min(ls + rs + numLDSs, MAX_VAL);
        }

        @Override
        public String toString() {
            return "(" + i + ", " + val + ", " + numLDSs + ")";
        }
    }

    public String toString() {
        traverse(root);
        System.out.println("----");
        return "----";
    }

    Triple nextLISVal(Node n, int lastI, long currK) {
        if (n == null) return new Triple(-1, -1, currK);
        // Iterate in decreasing order
        Triple rightResult = nextLISVal(n.right, lastI, currK);
        currK = rightResult.currK;
        if (rightResult.i != -1) return rightResult;  // Next LIS val has been found

        // Factor this node in (if it's in range)
        long newK = currK;
        if (n.i > lastI) {
            newK -= n.numLDSs;
            if (newK <= 0) {
                // This should be the next LIS val
                return new Triple(n.i, n.val, currK);
            }
        }

        // Keep looking
        return nextLISVal(n.left, lastI, newK);
    }

    void traverse(Node n) {
        if (n == null) return;
        traverse(n.left);
        System.out.println(n);
        traverse(n.right);
    }

    void add(int i, int val, long numLDSs) {
        root = add(root, i, val, numLDSs);
    }

    Node add(Node n, int i, int val, long numLDSs) {
        if (n == null) return new Node(i, val, numLDSs);
        if (val > n.val) {
            n.right = add(n.right, i, val, numLDSs);
        } else if (val < n.val) {
            n.left = add(n.left, i, val, numLDSs);
        } else {
            System.err.println("== error!");
        }

        n.update();
        return balance(n);
    }

    // Query for # of LDSs in nodes with value > val.
    long query(int val) {
        return query(root, val);
    }

    long query(Node n, int val) {
        if (n == null) return 0;
        if (val >= n.val) {
            // This node is not included
            return query(n.right, val);
        } else {
            // This node is included, along with the entire right subtree / maybe some of the left?
            long newVal = Math.min(n.numLDSs + ((n.right != null) ? n.right.sumSubtreeLDSs : 0), MAX_VAL);
            return Math.min(query(n.left, val) + newVal, MAX_VAL);
        }
    }

    Node balance(Node n) {
        if (Math.abs(n.bf) < 2) return n;
        else if (n.bf == 2) {
            if (n.right.bf >= 0) {
                return rightRightCase(n);
            } else {
                return rightLeftCase(n);
            }
        } else {
            if (n.left.bf <= 0) {
                return leftLeftCase(n);
            } else {
                return leftRightCase(n);
            }
        }
    }

    Node rightRightCase(Node n) {
        return rotateLeft(n);
    }

    Node rightLeftCase(Node n) {
        n.right = rotateRight(n.right);
        return rightRightCase(n);
    }

    Node leftLeftCase(Node n) {
        return rotateRight(n);
    }

    Node leftRightCase(Node n) {
        n.left = rotateLeft(n.left);
        return leftLeftCase(n);
    }

    Node rotateLeft(Node n) {
        Node newCenter = n.right;
        n.right = newCenter.left;
        newCenter.left = n;
        n.update();
        newCenter.update();
        return newCenter;
    }

    Node rotateRight(Node n) {
        Node newCenter = n.left;
        n.left = newCenter.right;
        newCenter.right = n;
        n.update();
        newCenter.update();
        return newCenter;
    }
}