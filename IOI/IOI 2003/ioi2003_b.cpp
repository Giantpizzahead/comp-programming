/**
 * Hash each section of the lines of code, and compare these hash values to determine if
 * two code sections are equivalent.
 * 
 * The basic idea for hashing a section of code is to assign each variable a number based on
 * the order it appears in the code. Sometimes, the order of two variables will be ambiguous
 * (if both are used in the same line on the right side, ex: _ = A + B). As soon as one appears
 * without the other, "decide" the order of these variables. Make sure the two variables on the
 * right are in increasing order. Then, just use a rolling string hash on the values.
 * 
 * Ex:
 * RA = RB + RC
 * RC = D + RE
 * RF = RF + RJ
 * RE = RF + RF
 * Is translated into:
 * 1 = 2 + 3
 * 3 = 5 + 4 (RE=4 and D=5 are decided once code line 4 is processed, since RE is used unambiguously)
 * 6 = 6 + 7
 * 4 = 6 + 6
 * So the values for the rolling hash are:
 * 1, 2, 3, 3, 4, 5, 6, 6, 7, 4, 6, 6
 * Since the two values on the right are put in increasing order.
 * 
 * The way this hash is generated, you can start at every first index, and iterate through
 * all values of the second index. That way, every section of code takes O(NUMH) time to compute.
 * 
 * Runtime: O(NUMH * (N^2 + M^2))
 * Memory: O(NUMH * max(N, M))
 * Accuracy: Dependent on NUMH, seems like 2 is enough, 3 would be safest
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int NUMH = 2;
const int POW[] = {7287, 18227, 29381};
const int MOD[] = {1000000007, 998251373, 1472912587};

int N, M;
vector<vector<int>> R, H, hashes;

void parseCode(int X, vector<vector<int>>& C) {
	C.resize(X);
	rep(i, 0, X) C[i].resize(NUMH);
	int currW = 0;
    unordered_map<string, int> strToW;
    string s;
    rep(i, 0, X) {
    	cin >> s;
    	if (strToW.find(s) == strToW.end()) strToW[s] = currW++;
    	C[i][0] = strToW[s];
    	cin >> s >> s;
    	if (strToW.find(s) == strToW.end()) strToW[s] = currW++;
    	C[i][1] = strToW[s];
    	cin >> s >> s;
    	if (strToW.find(s) == strToW.end()) strToW[s] = currW++;
    	C[i][2] = strToW[s];
    }
}

void genHashes(int L, vector<vector<int>>& C, void (*handleHash)(int, vector<ll>&)) {
    vector<ll> currH(NUMH);
    vector<int> xToW(L*3);
    vector<int> isUndecided(L*3);
    rep(i, 0, L) {
        // Generate rolling hashes
        int currW = 0;
        fill(all(xToW), -1);
        fill(all(currH), 0);
        rep(j, i, L) {
            int a = C[j][0], b = C[j][1], c = C[j][2];
            if (xToW[a] == -1) {
                // New mapping
                xToW[a] = currW++;
                isUndecided[a] = -1;
            } else if (isUndecided[a] != -1) {
                // Decide this mapping
                int o = isUndecided[a];
                if (xToW[a] > xToW[o]) {
                    // Switch the two
                    swap(xToW[a], xToW[o]);
                }
                isUndecided[a] = -1;
                isUndecided[o] = -1;
            }

            // The only case when we will have undecided is when:
            // 1) Both variables have not been seen yet
            // 2) Both variables have been seen, and have only been seen with each other

            if (xToW[b] == -1 && xToW[c] == -1) {
                // Both unknown; keep undecided
                xToW[b] = currW++;
                xToW[c] = currW++;
                isUndecided[b] = c;
                isUndecided[c] = b;
            } else if (xToW[b] != -1 && xToW[c] != -1 && isUndecided[b] == c && isUndecided[c] == b) {
                // Continue to be undecided
            } else {
                // No matter what, both values will be decided here
                if (xToW[b] == -1) {
                    xToW[b] = currW++;
                    isUndecided[b] = -1;
                } else if (isUndecided[b] != -1) {
                    int o = isUndecided[b];
                    if (xToW[b] > xToW[o]) swap(xToW[b], xToW[o]);
                    isUndecided[b] = -1;
                    isUndecided[o] = -1;
                }
                if (xToW[c] == -1) {
                    xToW[c] = currW++;
                    isUndecided[c] = -1;
                } else if (isUndecided[c] != -1) {
                    int o = isUndecided[c];
                    if (xToW[c] > xToW[o]) swap(xToW[c], xToW[o]);
                    isUndecided[c] = -1;
                    isUndecided[o] = -1;
                }
            }

            // Use values to generate hash
            int x = xToW[a] + 1;
            int y = min(xToW[b], xToW[c]) + 1;
            int z = max(xToW[b], xToW[c]) + 1;
            bool matched = true;
            rep(k, 0, NUMH) {
                currH[k] = (currH[k]*POW[k] + x) % MOD[k];
                currH[k] = (currH[k]*POW[k] + y) % MOD[k];
                currH[k] = (currH[k]*POW[k] + z) % MOD[k];
            }

            handleHash(j-i, currH);
        }
    }
}

int answer = 0;
vector<vector<unordered_set<int>>> hashSet;

void handleFirstHash(int s, vector<ll>& h) {
    // cerr << "first " << s;
    // rep(k, 0, NUMH) cerr << " " << h[k];
    // cerr << endl;

    // Add to hash set
    rep(k, 0, NUMH) {
        hashSet[s][k].insert(h[k]);
    }
}

void handleSecondHash(int s, vector<ll>& h) {
    // cerr << "second " << s;
    // rep(k, 0, NUMH) cerr << " " << h[k];
    // cerr << endl;

    // Compare same length hashes
    bool found = true;
    rep(k, 0, NUMH) {
        if (hashSet[s][k].find(h[k]) == hashSet[s][k].end()) {
            found = false;
            break;
        }
    }
    if (found) answer = max(s+1, answer);
}

void solve() {
    cin >> N >> M;
    parseCode(N, R);
    parseCode(M, H);

    // Init hash set
    hashSet.resize(max(N, M));
    rep(s, 0, max(N, M)) hashSet[s].resize(NUMH);
    
    // rep(i, 0, N) cout << R[i][0] << " " << R[i][1] << " " << R[i][2] << endl;
    // rep(i, 0, M) cout << H[i][0] << " " << H[i][1] << " " << H[i][2] << endl;

    genHashes(N, R, handleFirstHash);
    genHashes(M, H, handleSecondHash);
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}