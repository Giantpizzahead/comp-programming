#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 17;

int N, M;
int roundsNeeded[MAXN+1];
ll pow2[MAXN+1];
int R[MAXN][MAXN];

map<vector<int>, ll> currDP, nextDP;

void solve() {
    cin >> N >> M; M--;
    // N = 14;
    roundsNeeded[1] = 0;
    rep(i, 2, N+1) roundsNeeded[i] = roundsNeeded[(i+1)/2] + 1;
    pow2[0] = 1;
    rep(i, 1, N+1) pow2[i] = pow2[i-1] * 2;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cin >> R[i][j];
        }
    }

    vector<int> initMask(N, 0);
    nextDP[initMask] = 1;

    int i = 0, r = roundsNeeded[N];
    while (r > 0) {
        swap(nextDP, currDP);
        nextDP.clear();
        for (auto& p : currDP) {
            const vector<int>& mask = p.first;
            if (currDP[mask] == 0) continue;
            // cout << r << " " << i << ": ";
            // for (int x : mask) cout << x << " ";
            // cout << " = " << currDP[mask] << endl;
            if (i == N) {
                // Done with all rounds
                vector<int> newMask = mask;
                int numIn = 0;
                rep(j, 0, N) {
                    assert(newMask[j] != 0);
                    if (newMask[j] == 1) {
                        newMask[j] = 0;
                        numIn++;
                    }
                }
                // cout << roundsNeeded[numIn] << " " << numIn << endl;
                if (numIn != pow2[r-1]) {
                    // currDP[mask] = 0;
                    continue;  // Not good enough
                }
                // cout << "next round" << endl;
                nextDP[newMask] += currDP[mask];
            } else {
                // On person i
                if (mask[i] != 0) {
                    // No need to fight
                    nextDP[mask] += currDP[mask];
                    // currDP[mask] = 0;
                    continue;
                }
                // Skip i
                vector<int> newMask = mask;
                newMask[i] = 1;
                nextDP[newMask] += currDP[mask];
                // Battle with j
                rep(j, i+1, N) {
                    if (mask[j] != 0) continue;
                    newMask = mask;
                    // cout << "battle " << i << " " << j << endl;
                    if (R[i][j]) {
                        newMask[i] = 1, newMask[j] = 2;
                    } else {
                        newMask[i] = 2, newMask[j] = 1;
                    }
                    nextDP[newMask] += currDP[mask];
                }
            }
            // currDP[mask] = 0;
        }

        if (i == N) {
            i = 0;
            r--;
        } else {
            i++;
        }
    }

    vector<int> targetMask(N, 2);
    targetMask[M] = 0;
    cout << nextDP[targetMask] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
