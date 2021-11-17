#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int INF = 999999999;

int tryChar(vector<int>& S, int C, vector<vector<int>> adj) {
    int ans = 0;
    for (int x : S) {
        if (adj[x][C] == INF) return INF;
        else ans += adj[x][C];
    }
    return ans;
}

void countRows(int N, vector<vector<char>>& B, int& minXs, int& ways) {
    rep(i, 0, N) {
        // Row win
        int needed = 0;
        rep(j, 0, N) {
            if (B[i][j] == '.') needed++;
            else if (B[i][j] == 'O') {
                needed = -1;
                break;
            }
        }
        if (needed == -1) continue;
        else if (minXs == needed) ways++;
        else if (minXs > needed) {
            minXs = needed;
            ways = 1;
        }
    }
}

void solve() {
    int N; cin >> N;
    vector<vector<char>> B(N);
    rep(i, 0, N) B[i].resize(N);
    string str;
    rep(i, 0, N) {
        cin >> str;
        rep(j, 0, N) B[i][j] = str[j];
    }
    
    int minXs = INF, ways = 0;
    countRows(N, B, minXs, ways);
    // Rotate the board
    vector<vector<char>> rotB(N);
    rep(i, 0, N) rotB[i].resize(N);
    rep(i, 0, N) {
        rep(j, 0, N) {
            rotB[i][j] = B[N-1-j][i];
        }
    }
    countRows(N, rotB, minXs, ways);
    
    // Handle one overcount
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (B[i][j] == '.') {
                // Both row and column works?
                bool works = true;
                rep(k, 0, N) {
                    if (k == j) continue;
                    else if (B[i][k] != 'X') {
                        works = false;
                        break;
                    }
                }
                rep(k, 0, N) {
                    if (k == i) continue;
                    else if (B[k][j] != 'X') {
                        works = false;
                        break;
                    }
                }
                if (works) ways--;
            }
        }
    }
    
    /*
    cout << endl;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cout << B[i][j];
        }
        cout << endl;
    }
    cout << endl;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cout << rotB[i][j];
        }
        cout << endl;
    }
    */
    
    if (minXs == INF) cout << "Impossible\n";
    else cout << minXs << " " << ways << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}