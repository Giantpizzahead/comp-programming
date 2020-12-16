#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int MAXM = 1000;

int N, M;
string S;
string Q[MAXM];
vector<int> matches[MAXM];

struct Trie {
    struct Node {
        int depth, parentEdge;
        string currStr;
        Node* sufLink = nullptr;
        Node* dictLink = nullptr;
        Node* parent;
        Node* kids[256] = {};
        vector<int> endIndexes;

        Node(int depth, int parentEdge, Node* parent, string currStr) : depth(depth), parentEdge(parentEdge), parent(parent), currStr(currStr) {}

        void genLinks() {
            // Suffix link
            sufLink = parent->sufLink;
            while (!sufLink->kids[parentEdge]) {
                // Go to this node's suffix link
                if (sufLink->depth == 0) break;
                sufLink = sufLink->sufLink;
            }
            // Extend this node if possible (but not to whole string)
            if (sufLink->kids[parentEdge] && sufLink->kids[parentEdge] != this) {
                sufLink = sufLink->kids[parentEdge];
            }

            // Dictionary link
            if (!sufLink->endIndexes.empty()) dictLink = sufLink;
            else dictLink = sufLink->dictLink;
        }

        void insert(int i, string& str, int x) {
            if (i == str.length()) {
                // String ends here
                endIndexes.push_back(x);
            } else {
                // Continue down
                if (!kids[str[i]]) kids[str[i]] = new Node(depth+1, str[i], this, currStr + str[i]);
                kids[str[i]]->insert(i+1, str, x);
            }
        }

        void debug() {
            cout << endl << "(" << currStr << ", " << sufLink->currStr << ", " << dictLink->currStr << ")";
            for (int i = 0; i < 256; i++) {
                if (kids[i]) {
                    cout << " > ";
                    kids[i]->debug();
                    cout << " < ";
                }
            }
        }
    };

    Node* root;

    Trie() {
        root = new Node(0, -1, nullptr, "");
    }

    queue<Node*> toEval;
    void genLinks() {
        root->sufLink = root;
        root->dictLink = root;
        for (int i = 0; i < 256; i++) {
            if (root->kids[i]) toEval.push(root->kids[i]);
        }
        while (!toEval.empty()) {
            Node* n = toEval.front();
            toEval.pop();
            n->genLinks();
            for (int i = 0; i < 256; i++) {
                if (n->kids[i]) toEval.push(n->kids[i]);
            }
        }
    }

    void insert(string& str, int x) {
        root->insert(0, str, x);
    }

    void query(string& str) {
        Node* n = root;
        for (int i = 0; i < str.length(); i++) {
            while (!n->kids[str[i]]) {
                n = n->sufLink;
                if (n->depth == 0) break;
            }
            if (n->kids[str[i]]) n = n->kids[str[i]];
            // Find all substrings matching at this position
            Node* temp = n;
            while (temp != root) {
                for (int x : temp->endIndexes) {
                    matches[x].push_back(i-Q[x].length()+1);
                    // cout << i-x.length()+1 << " match " << Q[x] << endl;
                }
                temp = temp->dictLink;
            }
            // cout << i << " " << n->currStr << endl;
        }
    }
};

Trie trie;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> S;
    N = S.length();
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> Q[i];
        trie.insert(Q[i], i);
    }
    // Gen suffix and dict links
    trie.genLinks();
    trie.root->debug();
    cout << endl;

    // Query for all matches
    trie.query(S);
    for (int i = 0; i < M; i++) {
        cout << Q[i] << " -> ";
        for (int x : matches[i]) cout << x << ' ';
        cout << endl;
    }
    return 0;
}