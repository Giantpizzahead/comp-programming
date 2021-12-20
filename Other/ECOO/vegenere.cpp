#include <iostream>
#include <string>
#include <map>
using namespace std;
const int MAXN = 1e5+5;

int N;
string W[MAXN];
string S;

int answer;
string decrypted;

struct Node {
    Node* kids[26] = {};
    bool marked;

    void insert(int i, string& str) {
        if (i == str.length()) {
            marked = true;
            return;
        }
        if (!kids[str[i]-'A']) kids[str[i]-'A'] = new Node();
        kids[str[i]-'A']->insert(i+1, str);
    }

    void recycle() {
        for (int i = 0; i < 26; i++) {
            if (kids[i]) {
                kids[i]->recycle();
                delete kids[i];
                kids[i] = nullptr;
            }
        }
    }
};

struct Trie {
    Node* root = new Node();

    void insert(string& str) {
        root->insert(0, str);
    }
};

Trie trie;
map<int, int> states;

void addState(int i, int l) {
    if (states.find(i) != states.end()) states[i] = min(states[i], l);
    else states[i] = l;
}

inline int getChar(int w, int i) {
    int c1 = S[i] - 'A';
    int c2 = W[w][i % W[w].length()] - 'A' + 1;
    int c3 = ((c1 - c2) % 26 + 26) % 26;
    return c3;
}

void search(int w, int i, int l) {
    // cout << "search " << w << " " << i << " " << s << " " << l << endl;
    // Find next word
    Node* n = trie.root;
    string currWord = "";
    while (true) {
        if (n->marked) {
            // This could be valid; search this way
            addState(i, l + currWord.length() * currWord.length());
        }
        if (i == S.length()) return;
        int c3 = getChar(w, i);
        // cout << (char) (c3 + 'A') << endl;
        if (!n->kids[c3]) return;  // No valid interpretation
        else n = n->kids[c3];
        currWord += c3 + 'A';
        i++;
    }
}

void solve() {
    trie.root->recycle();
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> W[i];
        trie.insert(W[i]);
    }
    cin >> S;
    // Try each codeword
    answer = INT32_MAX;
    decrypted = "}";
    for (int i = 0; i < N; i++) {
        states[0] = 0;
        while (!states.empty()) {
            auto p = states.begin();
            if (p->first == S.length()) {
                // Found valid interpretation!
                string currDecrypt = "";
                for (int j = 0; j < S.length(); j++) {
                    currDecrypt += getChar(i, j) + 'A';
                }
                if (currDecrypt < decrypted) {
                    // Better
                    decrypted = currDecrypt;
                    answer = p->second;
                }
            }
            search(i, p->first, p->second);
            states.erase(p);
        }
        states.clear();
    }

    cout << decrypted.substr(0, 10) << ' ' << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 10; i++) {
        solve();
    }
    return 0;
}