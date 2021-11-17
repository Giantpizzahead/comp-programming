/**
 * Trie:
 * Let T = # of trie nodes, at most O(DN)
 * Let D = # of trie nodes above given leaf node
 * (or just depth, at most 500)
 * 
 * Knapsack is just pairs of:
 * (trie node, same trie node) = O(T)
 * (trie node, leaf in trie node's ST) = O(DN)
 * (leaf node, leaf node) = O(N^2)
 * 
 * Total runtime: O(T + DN + N^2) = O(2DN + N^2)
 * Worst case: O(2*500*2000 + 2000^2) = O(6000000)
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, K;
struct Trie {
    char c;
    int v;
    Trie* adj[26];

    Trie(char c) : c(c), v(0) {
        rep(i, 0, 26) adj[i] = nullptr;
    }

    vector<int>* solve() {
        vector<vector<int>*> childVals;
        int leafCnt = v;
        rep(i, 0, 26) {
            if (!adj[i]) continue;
            vector<int>* ret = adj[i]->solve();
            rep(i, 0, ret->size()) ret->at(i) += i*(i-1)/2;
            leafCnt += ret->size()-1;
            childVals.push_back(ret);
        }
        vector<int>* knapsack = new vector<int>(leafCnt+1);
        int currF = v;
        for (auto& child : childVals) {
            for (int i = currF; i >= 0; i--) {
                rep(k, 1, child->size()) {
                    knapsack->at(i+k) = max(knapsack->at(i) + child->at(k), knapsack->at(i+k));
                }
            }
            currF += child->size()-1;
        }
        return knapsack;
    }

    void add(string& str, int i = 0) {
        if (i == sz(str)) {
            v++;
            return;
        }
        int c = str[i] - 'a';
        if (!adj[c]) adj[c] = new Trie(str[i]);
        adj[c]->add(str, i+1);
    }

    void print(int i = 0) {
        rep(j, 0, i) debug << ' ';
        debug << c;
        vector<int>* ans = solve();
        for (int x : *ans) debug << ' ' << x;
        debug << endl;
        rep(j, 0, 26) if (adj[j]) adj[j]->print(i+1);
    }
};
Trie* trie = new Trie('R');

void solve() {
    cin >> N >> K;
    rep(i, 0, N) {
        string str; cin >> str;
        trie->add(str);
    }
    // trie->print();
    vector<int>* ans = trie->solve();
    cout << ans->at(K) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}