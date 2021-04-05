#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5001, MOD = 1e9+7;

int N, K;
int dp[MAXN];
string S;

struct Trie {
    struct Node {
        Node* kids[26];
        bool isWord = false;
        Node() {
            fill(kids, kids+26, nullptr);
        }
    };

    Node* root = new Node();

    void insert(string& str) {
        Node* n = root;
        rep(i, 0, sz(str)) {
            int e = str[i] - 'a';
            if (!n->kids[e]) n->kids[e] = new Node();
            n = n->kids[e];
        }
        n->isWord = true;
    }

    int extend(int x) {
        Node* n = root;
        int r = 0;
        for (int i = x; i > 0; i--) {
            int e = S[i] - 'a';
            if (!n->kids[e]) break;
            n = n->kids[e];
            if (n->isWord) {
                r = (r + dp[i-1]) % MOD;
            }
        }
        return r;
    }
} trie;

void solve() {
    cin >> S >> K;
    N = sz(S);
    S = " " + S;
    string word;
    rep(i, 0, K) {
        cin >> word;
        reverse(all(word));
        trie.insert(word);
    }
    dp[0] = 1;
    rep(i, 1, N+1) {
        dp[i] = trie.extend(i);
    }
    cout << dp[N] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}