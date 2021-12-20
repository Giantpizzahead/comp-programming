import java.util.*;
import java.io.*;

public class bundling {
    int N, K;
    Trie trie;

    bundling(BufferedReader in, PrintWriter out, int t) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        trie = new Trie();
        for (int i = 0; i < N; i++) trie.addString(in.readLine());

        long answer = trie.solve();
        out.println("Case #" + (t+1) + ": " + answer);
    }

    class Trie {
        TrieNode root = new TrieNode(0);
        long answer = 0;

        long solve() {
            root.solve();
            return answer;
        }

        void addString(String str) {
            root.addString(str, 0);
        }

        class TrieNode {
            TrieNode[] children;
            int numStrings, depth;

            TrieNode(int depth) {
                children = new TrieNode[26];
                numStrings = 0;
                this.depth = depth;
            }

            void addString(String str, int i) {
                numStrings++;
                if (i == str.length()) return;
                if (children[str.charAt(i) - 'A'] == null) {
                    children[str.charAt(i) - 'A'] = new TrieNode(depth + 1);
                }
                children[str.charAt(i) - 'A'].addString(str, i+1);
            }

            int solve() {
                int usedStrings = 0;
                for (TrieNode child : children) {
                    if (child != null) usedStrings += child.solve();
                }
                // If enough strings here, form a group with them!
                int groups = (numStrings - usedStrings) / K;
                usedStrings += groups * K;
                answer += (long) groups * depth;
                return usedStrings;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new bundling(in, out, i);
        in.close();
        out.close();
    }
}
