#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, M;
bool canUse[26];
string words[MAXN];
string str;

struct Trie {
    Trie* kids[26];
    bool isWord;

    Trie() {
        for (int i = 0; i < 26; i++) kids[i] = nullptr;
        isWord = false;
    }

    void clear() {
        for (int i = 0; i < 26; i++) {
            if (kids[i]) kids[i]->clear();
        }
        delete this;
    }

    void insert(string& s, int i) {
        if (i == s.length()) {
            isWord = true;
            return;
        }
        if (!kids[s[i]-'a']) {
            kids[s[i]-'a'] = new Trie();
        }
        kids[s[i]-'a']->insert(s, i+1);
    }

    // Returns result of person who plays this turn (+1 win, 0 draw, -1 lose)
    int solve() {
        if (isWord) {
            // Base case
            return -1;
        }
        int bestRes = -1;
        for (int i = 0; i < 26; i++) {
            if (kids[i]) {
                int currRes = kids[i]->solve();
                if (currRes == -1) bestRes = 1;
                else if (currRes == 0 && bestRes != 1) bestRes = 0;
            } else if (canUse[i] && bestRes != 1) bestRes = 0;
        }
        return bestRes;
    }
};

Trie* trie = new Trie();

void solve() {
    cin >> N >> M;
    cin >> str;
    for (int i = 0; i < 26; i++) canUse[i] = false;
    for (int i = 0; i < N; i++) canUse[str[i]-'a'] = true;
    trie->clear();
    trie = new Trie();
    for (int i = 0; i < M; i++) {
        cin >> words[i];
        trie->insert(words[i], 0);
    }
    int result = trie->solve();
    if (result == 1) cout << "Alice wins\n";
    else if (result == 0) cout << "Draw\n";
    else cout << "Bob wins\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Game #" << i << ": ";
        solve();
    }
    return 0;
}