import java.util.*;
import java.io.*;

public class arrsimplequeries {
    Treap treap;
    int N, M;
    int[] arr;

    arrsimplequeries(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        treap = new Treap();
        for (int i = 0; i < N; i++) {
            treap.insert(i, arr[i]);
        }
//        treap.printTreap();
//        for (int i = 0; i < N; i++) System.out.println(treap.query(i));

        int t, l, r;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            t = Integer.parseInt(st.nextToken());
            l = Integer.parseInt(st.nextToken()) - 1;
            r = Integer.parseInt(st.nextToken());
            treap.split(r);
            Treap treapLeft = new Treap(treap.root.left);
            Treap treapRight = new Treap(treap.root.right);
            treapLeft.split(l);
            Treap treapMiddle = new Treap(treapLeft.root.right);
            treapLeft = new Treap(treapLeft.root.left);
//            System.out.print("left ");
//            treapLeft.printTreap();
//            System.out.print("middle ");
//            treapMiddle.printTreap();
//            System.out.print("right ");
//            treapRight.printTreap();
            if (t == 1) {
                // Add to front
                treapMiddle.merge(treapLeft);
                treapMiddle.merge(treapRight);
                treap = treapMiddle;
            } else {
                // Add to back
                treapLeft.merge(treapRight);
                treapLeft.merge(treapMiddle);
                treap = treapLeft;
            }
            // treap.printTreap();
        }

        int[] finalArr = new int[N];
        for (int i = 0; i < N; i++) finalArr[i] = treap.query(i);
        out.println(Math.abs(finalArr[0] - finalArr[N-1]));
        for (int i = 0; i < N; i++) {
            if (i != 0) out.print(' ');
            out.print(finalArr[i]);
        }
        out.println();
    }

    static class Treap {
        static Random random = new Random(11234234);
        Node root;

        Treap() {}

        Treap(Node root) {
            this.root = root;
        }

        static class Node {
            Node left, right;
            int value, stSize;
            long priority;

            Node(int value, long priority) {
                this.value = value;
                this.priority = priority;
                stSize = 1;
            }

            void update() {
                stSize = 1;
                if (left != null) stSize += left.stSize;
                if (right != null) stSize += right.stSize;
            }

            void printNode() {
                if (left != null) left.printNode();
                System.out.print(this);
                System.out.print(", ");
                if (right != null) right.printNode();
            }

            @Override
            public String toString() {
                return Integer.toString(value);
                // return "(" + value + ", " + stSize + ", " + priority + ")";
            }
        }

        /**
         * Inserts a node with the given value and priority right before the given index.
         * Returns the root of the treap (possibly modified).
         */
        void insert(int index, int value) {
            root = insert(root, index, value, random.nextInt(100)); //Math.abs(random.nextLong()));
        }

        Node insert(Node n, int index, int value, long priority) {
            if (n == null) {
                // Insert here!
                return new Node(value, priority);
            }

            int leftSTSize = (n.left == null) ? 0 : n.left.stSize;
            if (leftSTSize >= index) {
                // Insert in left
                n.left = insert(n.left, index, value, priority);
                // Rotate if necessary
                if (n.left.priority < n.priority) {
                    return rotateRight(n);
                } else {
                    n.update();
                    return n;
                }
            } else {
                // Insert in right
                n.right = insert(n.right, index - leftSTSize - 1, value, priority);
                // Rotate if necessary
                if (n.right.priority < n.priority) {
                    return rotateLeft(n);
                } else {
                    n.update();
                    return n;
                }
            }
        }

        /**
         * Queries for the value at a given index in the treap. Returns -1 if that index
         * is not found.
         */
        int query(int index) {
            return query(root, index);
        }

        int query(Node n, int index) {
            if (n == null) return -1;

            int leftSTSize = (n.left == null) ? 0 : n.left.stSize;
            if (leftSTSize > index) {
                // In left subtree (or not found)
                return query(n.left, index);
            } else if (leftSTSize == index) {
                // This is the right node!
                return n.value;
            } else {
                // In right subtree (or not found)
                return query(n.right, index - leftSTSize - 1);
            }
        }

        /**
         * Merges this treap with another treap. All elements in this treap must be less
         * than the elements in the other treap!
         */
        void merge(Treap oTreap) {
            root = join(root, oTreap.root);
        }

        Node join(Node r1, Node r2) {
            if (r1 == null && r2 == null) return null;
            else if (r1 == null) return r2;
            else if (r2 == null) return r1;
            else if (r1.priority > r2.priority) {
                Node oldRight = r1.right;
                r1.right = r2;
                r2.left = join(oldRight, r2.left);
                r2.update();
                r1.update();
                return r1;
            } else {
                Node oldLeft = r2.left;
                r2.left = r1;
                r1.right = join(r1.right, oldLeft);
                r1.update();
                r2.update();
                return r2;
            }
        }

        /**
         * Splits the treap right before the given index. root.left will contain all
         * nodes with indexes [0, i), and root.right contains [i, INF). Make sure to
         * discard the root node after calling this method!
         */
        void split(int index) {
            root = insert(root, index, -1, -1);
        }

        Node rotateLeft(Node n) {
            Node newRoot = n.right;
            n.right = n.right.left;
            newRoot.left = n;
            n.update();
            newRoot.update();
            return newRoot;
        }

        Node rotateRight(Node n) {
            Node newRoot = n.left;
            n.left = n.left.right;
            newRoot.right = n;
            n.update();
            newRoot.update();
            return newRoot;
        }

        void printTreap() {
            System.out.print("Treap[");
            if (root != null) root.printNode();
            System.out.println("]");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new arrsimplequeries(in, out);
        in.close();
        out.close();
    }
}
