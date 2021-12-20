#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll POWH = 61;
const ll MOD = 239487234978359;

int N, R;
ll powRemove;
unordered_map<string, int> codeToI;
set<ll> hashes;
string str;

void solve() {
    cin >> str;
    N = str.length();
    hashes.clear();
    codeToI.clear();
    string code;
    int x;
    for (int i = 0; i < 64; i++) {
        cin >> code >> x;
        codeToI[code] = x + 1;
        // cout << code << x;
    }
    cin >> R;
    R /= 3;
    powRemove = 1;
    for (int i = 1; i < R; i++) {
        powRemove *= POWH;
        powRemove %= MOD;
    }
    for (int i = 0; i < 3; i++) {
        // Sliding window hash
        ll H = 0;
        int currL = 0;
        for (int j = i; j <= N-3; j += 3) {
            H *= POWH;
            H %= MOD;
            code = str[j];
            code += str[j+1];
            code += str[j+2];
            // cout << code << endl;
            H += codeToI[code];
            currL++;
            if (currL == R) {
                // cout << "insert " << H << endl;
                hashes.insert(H);
                // Remove last codon
                int offset = (currL-1)*3;
                code = str[j-offset];
                code += str[j-offset+1];
                code += str[j-offset+2];
                // cout << code << endl;
                H -= codeToI[code] * powRemove;
                H %= MOD;
                if (H < 0) H += MOD;
                currL--;
            }
            // cout << "hash " << H << endl;
        }
    }
    cout << hashes.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}