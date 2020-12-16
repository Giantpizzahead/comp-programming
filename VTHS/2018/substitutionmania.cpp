#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 12;

int N;
int currCipher[MAXN];
bool used[26];
string strD, strE, D, E, enc;
string revCiphers[MAXN], ciphers[MAXN];

string encode(string& a, string& b) {
    string c;
    c.resize(a.size());
    for (int i = 0; i < c.size(); i++) {
        if (a[i] == ' ') c[i] = ' ';
        else c[i] = b[a[i]-'a'];
    }
    return c;
}

int genHash(int C) {
    int hash = 0;
    for (int i = C-1; i >= 0; i--) {
        hash *= 12;
        hash += currCipher[i];
    }
    return hash;
}

unordered_map<string, int> hashes;

void genRev(string& str, int x) {
    if (x == (N+1)/2) {
        // Add to hashes
        // cout << "add " << str << " " << genHash((N+1)/2) << endl;
        hashes.emplace(str, genHash((N+1)/2));
    } else {
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                used[i] = true;
                currCipher[x] = i;
                string newStr = encode(str, revCiphers[i]);
                genRev(newStr, x+1);
                used[i] = false;
            }
        }
    }
}

void genFront(string& str, int x) {
    if (x == N/2) {
        // Check for hash
        // cout << "check " << str << " " << genHash(N/2) << endl;
        auto ptr = hashes.find(str);
        if (ptr == hashes.end()) return;
        // Valid config found!
        // cout << "config " << ptr->second << endl;
        // Know the order to apply
        int hash = ptr->second;
        for (int i = 0; i < (N+1)/2; i++) {
            enc = encode(enc, revCiphers[hash % 12]);
            hash /= 12;
        }
        for (int i = N/2-1; i >= 0; i--) {
            enc = encode(enc, revCiphers[currCipher[i]]);
        }
        cout << enc << endl;
    } else {
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                used[i] = true;
                currCipher[x] = i;
                string newStr = encode(str, ciphers[i]);
                genFront(newStr, x+1);
                used[i] = false;
            }
        }
    }
}

void solve() {
    getline(cin, strD);
    getline(cin, strE);
    for (int i = 0; i < strD.size(); i++) {
        if (strD[i] == ' ' || used[strD[i]-'a']) continue;
        D += strD[i];
        E += strE[i];
        used[strD[i]-'a'] = true;
    }
    cin >> N;
    cin.get();
    for (int i = 0; i < N; i++) {
        getline(cin, ciphers[i]);
        revCiphers[i].resize(26);
        for (int j = 0; j < 26; j++) {
            revCiphers[i][ciphers[i][j]-'a'] = 'a'+j;
        }
    }
    getline(cin, enc);

    if (N == 1) {
        // Special case
        cout << encode(enc, revCiphers[0]) << endl;
        return;
    }
    for (int i = 0; i < N; i++) used[i] = false;

    genRev(E, 0);
    genFront(D, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}