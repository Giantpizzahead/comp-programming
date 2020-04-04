/*
Solution: Use an AVL tree to efficiently find the max blockage time from -INF to i, shift all
elements from -INF to i left 1, and add a new blockage time. Use lazy propagation to shift
the nodes.

why avl tree whyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy :(((((((

Runtime: O(N * log(N))
*/

import java.io.*;
import java.util.*;

public class boardingAVL {
    int N;
    Cow[] cows;

    boardingAVL() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("boarding.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        cows = new Cow[N];
        int s, t;
        for (int i = N-1; i >= 0; i--) {
            st = new StringTokenizer(fin.readLine());
            s = Integer.parseInt(st.nextToken());
            t = Integer.parseInt(st.nextToken());
            cows[i] = new Cow(s, t);
        }
        fin.close();
        int answer = simulate();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("boarding.out")));
        fout.println(answer);
        fout.close();
    }

    int simulate() {
        BBST bbst = new BBST();
        int answer = 0;
        for (int i = 0; i < N; i++) {
            int distToSeat = cows[i].s + i;

            // Get current blockage
            Node blockage = bbst.query(cows[i].s);
            // System.out.println("Blockage got from " + cows[i].s + " = " + blockage);
            int timeTaken;
            if (blockage == null) timeTaken = distToSeat + cows[i].t;
            else {
                timeTaken = blockage.adjustValue(cows[i].s) + cows[i].t;
                // Shift current blockages
                bbst.shift(blockage.index);
            }

            // System.out.println("Time taken for cow " + (i + 1) + ": " + timeTaken);
            answer = Math.max(timeTaken, answer);

            // Add new blockage to bbst
            bbst.add(cows[i].s, timeTaken);
            // System.out.println(bbst);
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        new boardingAVL();
    }
}

class BBST {
    Node root;
    int size;

    /**
     * Adds a node with the given index and value.
     */
    void add(int index, int value) {
        if (size == 0) {
            root = new Node(index, value);
            size++;
        } else {
            // First, make sure the node isn't useless (previous value always beats this one)
            Node previous = query(index);
            Node curr = new Node(index, value);
            if (previous != null && previous.adjustValue(index) >= curr.adjustValue(index)) return;
            // Add the node
            root = add(root, index, value);
            // Remove any outdated nodes
            int lastIndex = index;
            while (size > 1) {
                Node next = higher(lastIndex);
                // System.out.println("Higher " + lastIndex + " = " + next);
                if (next != null && curr.adjustValue(index) >= next.adjustValue(index)) {
                    remove(next.index);
                    lastIndex = next.index;
                } else break;
            }
        }
    }

    Node add(Node node, int index, int value) {
        if (node == null) {
            size++;
            return new Node(index, value);  // Add new node here
        }

        // First, propagate changes if needed
        propagate(node);
        if (index == node.index) {
            // Duplicate found; set value to max of both values
            node.value = Math.max(value, node.value);
        } else if (index < node.index) {
            // Recurse on left node
            node.left = add(node.left, index, value);
        } else {
            // Recurse on right node
            node.right = add(node.right, index, value);
        }

        update(node);
        return balance(node);
    }

    /**
     * Removes the node with the given index.
     */
    void remove(int index) {
        root = remove(root, index);
    }

    Node remove(Node node, int index) {
        if (node == null) return null;

        // First, propagate changes if needed
        propagate(node);
        if (index == node.index) {
            // Node to remove found; check subtrees
            size--;
            if (node.left == null) {
                // Either no subtrees, or only right subtree
                return node.right;
            } else if (node.right == null) {
                // Only left subtree
                return node.left;
            } else {
                // Has both subtrees; arbitrarily choose maximum node on left side to switch
                Node maxLeft = getMaxNode(node.left);
                node.index = maxLeft.index;
                node.value = maxLeft.value;
                size++;
                node.left = remove(node.left, maxLeft.index);
            }
        } else if (index < node.index) {
            // Recurse on left node
            node.left = remove(node.left, index);
        } else {
            // Recurse on right node
            node.right = remove(node.right, index);
        }

        update(node);
        return balance(node);
    }

    Node getMaxNode(Node node) {
        propagate(node);
        while (node.right != null) {
            node = node.right;
            propagate(node);
        }
        return node;
    }

    /**
     * Gets the first node with index lower than or equal to the index given. Returns null if there are no lower nodes.
     */
    Node query(int index) {
        return query(root, index);
    }

    Node query(Node node, int index) {
        if (node == null) return null;

        // First, propagate changes if needed
        propagate(node);
        if (index == node.index + node.delta) {
            // Exact value found; return it
            return node;
        } else if (index < node.index + node.delta) {
            // Recurse on left node
            return query(node.left, index);
        } else {
            // This node could be the max one, but recurse on right node first to make sure
            Node right = query(node.right, index);
            if (right != null) return right;
            else return node;
        }
    }

    /**
     * Gets the first node with index explicitly higher than the index given. Returns null if there are no higher nodes.
     */
    Node higher(int index) {
        return higher(root, index);
    }

    Node higher(Node node, int index) {
        if (node == null) return null;

        // First, propagate changes if needed
        propagate(node);
        if (index < node.index + node.delta) {
            // This node could be the min one, but recurse on left node first to make sure
            Node left = higher(node.left, index);
            if (left != null) return left;
            else return node;
        } else {
            // Recurse on right node
            return higher(node.right, index);
        }
    }

    /**
     * Shifts all nodes with index equal to or below the given index 1 position to the left.
     */
    void shift(int index) {
        // Shift nodes
        shift(root, index);

        // Remove any outdated nodes
        Node curr = query(index - 1);
        int lastIndex = index - 1;
        while (size > 1) {
            Node next = higher(lastIndex);
            // System.out.println("Higher " + lastIndex + " = " + next);
            if (next != null && curr.adjustValue(index) >= next.adjustValue(index)) {
                remove(next.index);
                lastIndex = next.index;
            } else break;
        }
    }

    void shift(Node node, int index) {
        if (node == null) return;

        // First, propagate changes if needed
        propagate(node);
        if (index == node.index) {
            // Exact value found; do shifting
            node.index--;
            if (node.left != null) node.left.delta--;
        } else if (index < node.index) {
            // Recurse on left node
            shift(node.left, index);
        } else {
            // Update shift value and recurse on right node
            node.index--;
            if (node.left != null) node.left.delta--;
            if (node.right != null) {
                shift(node.right, index);
            }
        }
    }

    void propagate(Node node) {
        node.index += node.delta;
        if (node.left != null) node.left.delta += node.delta;
        if (node.right != null) node.right.delta += node.delta;
        node.delta = 0;
    }

    void update(Node node) {
        int lh = (node.left != null) ? node.left.height : -1;
        int rh = (node.right != null) ? node.right.height : -1;
        node.height = Math.max(lh, rh) + 1;
        node.bf = rh - lh;
    }

    Node balance(Node node) {
        if (Math.abs(node.bf) < 2) return node;
        else if (node.bf == 2) {
            if (node.right.bf >= 0) {
                return rightRightCase(node);
            } else {
                return rightLeftCase(node);
            }
        } else {
            if (node.left.bf <= 0) {
                return leftLeftCase(node);
            } else {
                return leftRightCase(node);
            }
        }
    }

    Node rightRightCase(Node node) {
        return leftRotation(node);
    }

    Node rightLeftCase(Node node) {
        node.right = rightRotation(node.right);
        return rightRightCase(node);
    }

    Node leftLeftCase(Node node) {
        return rightRotation(node);
    }

    Node leftRightCase(Node node) {
        node.left = leftRotation(node.left);
        return leftLeftCase(node);
    }

    Node leftRotation(Node node) {
        Node newCenter = node.right;
        propagate(node);
        propagate(newCenter);
        node.right = newCenter.left;
        newCenter.left = node;
        update(node);
        update(newCenter);
        return newCenter;
    }

    Node rightRotation(Node node) {
        Node newCenter = node.left;
        propagate(node);
        propagate(newCenter);
        node.left = newCenter.right;
        newCenter.right = node;
        update(node);
        update(newCenter);
        return newCenter;
    }

    String printNodes(Node node) {
        if (node == null) return "";
        return printNodes(node.left) + ((node.left != null) ? ", " : "") + node + ((node.right != null) ? ", " : "") + printNodes(node.right);
    }

    @Override
    public String toString() {
        return "BBST[" + printNodes(root) + "]";
    }
}

class Node {
    int index, value, delta, height, bf;
    Node left, right;
    Node(int index, int value) {
        this.index = index;
        this.value = value;
        this.delta = 0;
        this.height = 0;
        this.bf = 0;
    }
    int adjustValue(int queryIndex) {
        return value + 1 + queryIndex - (index + delta);
    }

    @Override
    public String toString() {
        return "(" + (index + delta) + ", " + value + ")";
    }
}

class Cow {
    int s, t;
    Cow(int s, int t) {
        this.s = s;
        this.t = t;
    }
}