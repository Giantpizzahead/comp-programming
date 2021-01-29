#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

const int MAXK = 1e6+5, MAXD = 31-22, MOD = 1e9+7;

int N, K;
int numAbove[MAXK], abovePre[MAXK];
bool exists[MAXK];

struct Trie {
    struct Node {
        int v = 0;
        Node* e0 = nullptr;
        Node* e1 = nullptr;
    };

    Node* root = new Node();

    void insert(int v, int d, Node* n) {
        if (d == -1) {
            n->v++;
        } else if (v & (1 << d)) {
            // Bit is 1
            if (!n->e1) n->e1 = new Node();
            insert(v, d-1, n->e1);
            n->v++;
        } else {
            // Bit is 0
            if (!n->e0) n->e0 = new Node();
            insert(v, d-1, n->e0);
            n->v++;
        }
    }

    int calcAbove(int v, int d, Node* n) {
        if (d == -1 || !n) return 0;
        bool req = (K & (1 << d)) == 0;
        // cout << "above " << v << " " << d << " " << req << endl;
        if (v & (1 << d)) {
            // Bit is 1
            if (req) {
                // Only same can be paired
                return calcAbove(v, d-1, n->e1);
            } else {
                // All same will be paired; check diff
                return (n->e1 ? n->e1->v : 0) + calcAbove(v, d-1, n->e0);
            }
        } else {
            // Bit is 0
            if (req) {
                return calcAbove(v, d-1, n->e0);
            } else {
                return (n->e0 ? n->e0->v : 0) + calcAbove(v, d-1, n->e1);
            }
        }
    }

    void print(Node* n, int indent = 0) {
        if (n->e0) print(n->e0, indent+1);
        rep(i, 0, indent) cout << ' ';
        cout << n->v << endl;
        if (n->e1) print(n->e1, indent+1);
    }
};
Trie trie;

void solve() {
    cin >> N >> K;
    int l, r;
    rep(i, 0, N) {
        cin >> l >> r;
        rep(j, l, r+1) {
            trie.insert(j, MAXD, trie.root);
            exists[j] = true;
        }
    }
    trie.print(trie.root);

    // Find num above
    rep(j, 1, MAXK) {
        if (exists[j]) {
            numAbove[j] = trie.calcAbove(j, MAXD, trie.root);
            cout << j << ": " << numAbove[j] << endl;
        }
    }
    for (int j = MAXK-2; j >= 1; j--) {
        abovePre[j] = (abovePre[j+1] + numAbove[j]) % MOD;
    }
    // Count triples
    int answer = 0;
    rep(j, 1, MAXK) {
        if (exists[j]) {
            answer = (answer + abovePre[j+1]) % MOD;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}