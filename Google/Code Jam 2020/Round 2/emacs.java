import java.io.*;
import java.util.*;

public class emacs {
    final long INF = 98765412323456787L;
    Node root;
    int K, Q;
    Node[] node;
    int[] endingLoc, L, R, P, queryS, queryE;
    char[] str;

    class Node {
        int l, r, id;
        int[] costLeft, costRight;
        Node parent;
        ArrayList<Node> innerNodes;

        Node(int l, int r, int id, Node outer) {
            parent = outer;
            this.l = l;
            this.r = r;
            this.id = id;
            innerNodes = new ArrayList<>(2);
            // Gen innerNodes
            for (int i = l + 1; i < r; i++) {
                if (str[i] == '(') {
                    innerNodes.add(new Node(i, endingLoc[i], innerNodes.size(), this));
                }
            }
        }

        void genCosts() {
            costLeft = new int[innerNodes.size() + 1];
            costRight = new int[innerNodes.size() + 1];

            // Option 1: Direct path
            costLeft[0] = 1;
            for (int i = 1; i <= innerNodes.size(); i++) {
                costLeft[i] = costLeft[i-1] + 2;
            }

            // Option 2: Loop over
            costLeft[innerNodes.size()] = 1;
            for (int i = innerNodes.size() - 1; i >= 0; i--) {
                costLeft[i] = costLeft[i+1] + 2;
            }

            // Option 2: Loop over
            costRight[0] = 1;
            for (int i = 1; i <= innerNodes.size(); i++) {
                costRight[i] = costRight[i-1] + 2;
            }

            // Option 1: Direct path
            costRight[innerNodes.size()] = 1;
            for (int i = innerNodes.size() - 1; i >= 0; i--) {
                costRight[i] = costRight[i+1] + 2;
            }
        }

        int query(int s, int e, int c) {
            if (e >= l && e <= r) return 1;  // Just take 1 jump
            long best = INF;
            // Option 1: Go to outer parentheses, and try to reach e from the other side
            if (s < e) {
                // Going to right outer parentheses
                int cost = Math.min(parent.costLeft[id] + (s == l ? 0 : 1), parent.costRight[id] + (s == r ? 0 : 1));
                // Reach e from that side

            }
            return -1;
        }

        int findInnerI(int i) {
            int low = 0, high = innerNodes.size() - 1;
            while (low < high) {
                int mid = (low + high + 1) / 2;
                if (innerNodes.get(mid).l > i) {
                    high = mid - 1;
                } else low = mid;
            }
            return low;
        }
    }

    emacs(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        K = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        str = in.readLine().toCharArray();

        L = new int[K];
        R = new int[K];
        P = new int[K];
        queryS = new int[Q];
        queryE = new int[Q];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < K; i++) L[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < K; i++) R[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < K; i++) P[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < Q; i++) queryS[i] = Integer.parseInt(st.nextToken()) - 1;
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < Q; i++) queryE[i] = Integer.parseInt(st.nextToken()) - 1;

        endingLoc = new int[K];
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < K; i++) {
            if (str[i] == '(') stack.add(i);
            else endingLoc[stack.pop()] = i;
        }

        // Gen nodes
        root = new Node(-1, K, -1, null);

        // Answer queries
        long sum = 0;
        for (int i = 0; i < Q; i++) {
            int s = queryS[i];
            int e = queryE[i];
            sum += node[s].query(s, e, 0);
        }

        out.println("Case #" + tn + ": " + sum);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new emacs(in, out, i);
        in.close();
        out.close();
    }
}
