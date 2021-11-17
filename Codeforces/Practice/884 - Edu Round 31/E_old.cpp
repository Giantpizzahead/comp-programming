#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXM = 16384;

int N, M;
int A[MAXM], B[MAXM];

void solve() {
    cin >> N >> M;
    int answer = 0, currLabel = 2;
    map<int, int> newNums;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M/4) {
            int x;
            if (S[j] >= '0' && S[j] <= '9') x = S[j] - '0';
            else x = S[j] - 'A' + 10;
            B[4*j] = (x & 0b1000) != 0;
            B[4*j+1] = (x & 0b0100) != 0;
            B[4*j+2] = (x & 0b0010) != 0;
            B[4*j+3] = (x & 0b0001) != 0;
        }
        // Transition to next row
        int sj = -1, startLabel = currLabel, compLabel = -1;
        rep(j, 0, M) {
            if (B[j] == 1) {
                if (sj == -1) {
                    // New component
                    sj = j;
                    compLabel = ++currLabel;
                    answer++;
                }
                B[j] = compLabel;
                auto ptr = newNums.find(A[j]);
                if (ptr != newNums.end()) A[j] = ptr->second;
                if (A[j] != 0 && A[j] != compLabel) {
                    // Connect to top component
                    if (A[j] <= startLabel) {
                        // Old component; renumber
                        newNums.emplace(A[j], compLabel);
                        answer--;
                    } else {
                        // New component
                        compLabel = A[j];
                        rep(k, sj, j+1) B[k] = compLabel;
                        answer--;
                    }
                }
            } else {
                if (sj != -1) {
                    // End of component
                    sj = -1;
                    compLabel = -1;
                }
            }
        }
        newNums.clear();
        // rep(j, 0, M) cout << B[j];
        // cout << endl;
        swap(A, B);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}