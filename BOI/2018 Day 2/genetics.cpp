#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 4100;
const int H = 3;
const int C = 4;

int N, M, K;
ll V[H][MAXN];
int S[MAXN][MAXN];
ll hashed[H][C][MAXN];
ll targetSum[H];

vector<int> checkI, checkJ;
void solve() {
    cin >> N >> M >> K;
    rep(i, 0, N) {
        string str; cin >> str;
        rep(j, 0, M) {
            if (str[j] == 'A') S[i][j] = 0;
            if (str[j] == 'C') S[i][j] = 1;
            if (str[j] == 'G') S[i][j] = 2;
            if (str[j] == 'T') S[i][j] = 3;
        }
    }
    
    // Generate random hash values
    srand(3789257);
    rep(h, 0, H) {
        rep(i, 0, N) {
            V[h][i] = rand() % 1000000000 + 1;
        }
    }

    // Fill hash sums
    rep(h, 0, H) {
        rep(i, 0, N) {
            targetSum[h] += V[h][i] * K;
            rep(j, 0, M) hashed[h][S[i][j]][j] += V[h][i];
        }
    }

    // Check each string
    rep(i, 0, N) {
        bool match = true;
        rep(h, 0, H) {
            // Exclude this string
            ll target = targetSum[h] - V[h][i] * K;
            // Calculate hash
            ll currSum = 0;
            rep(j, 0, M) {
                rep(c, 0, C) if (S[i][j] != c) currSum += hashed[h][c][j];
            }
            // cout << target << " vs " << currSum << " for " << i << endl;
            if (target != currSum) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << i+1 << '\n';
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}