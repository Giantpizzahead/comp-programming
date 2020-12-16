#include <iostream>
using namespace std;
using ll = long long;
const int MAXN = 3605;
const int MOD = 998244353;

int H, W, N;
int rowDP[MAXN][MAXN], colDP[MAXN][MAXN], fact[MAXN][MAXN];
int rowsOpen, colsOpen;
bool rowUsed[MAXN], colUsed[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> H >> W >> N;
    int a, b, c, d;
    for (int i = 0; i < N; i++) {
        cin >> a >> b >> c >> d;
        rowUsed[a] = true;
        rowUsed[c] = true;
        colUsed[b] = true;
        colUsed[d] = true;
    }
    rowUsed[0] = true;
    colUsed[0] = true;
    rowsOpen = 0;
    for (int i = 1; i <= H; i++) {
        if (!rowUsed[i]) rowsOpen++;
    }
    colsOpen = 0;
    for (int i = 1; i <= W; i++) {
        if (!colUsed[i]) colsOpen++;
    }
    for (int i = 1; i <= max(H, W) + 1; i++) {
        fact[i][i-1] = 1;
        for (int j = i; j <= max(H, W) + 1; j++) {
            fact[i][j] = (ll) fact[i][j-1] * j % MOD;
        }
    }
    
    rowDP[0][0] = 1;
    for (int i = 1; i <= H; i++) {
        for (int j = 0; j <= H; j++) {
            rowDP[i][j] = rowDP[i-1][j];
            if (j != 0 && !rowUsed[i] && !rowUsed[i-1]) rowDP[i][j] += rowDP[i-2][j-1];
            rowDP[i][j] %= MOD;
        }
    }

    colDP[0][0] = 1;
    for (int i = 1; i <= W; i++) {
        for (int j = 0; j <= W; j++) {
            colDP[i][j] = colDP[i-1][j];
            if (j != 0 && !colUsed[i] && !colUsed[i-1]) colDP[i][j] += colDP[i-2][j-1];
            colDP[i][j] %= MOD;
        }
    }

    ll answer = 0;
    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= W; j++) {
            int spareRows = rowsOpen - i * 2;
            int spareCols = colsOpen - j * 2;
            if (spareRows < j || spareCols < i) continue;
            // cout << i << " " << j << " " << spareRows - j + 1 << " " << spareRows << endl;
            // Combine these
            ll ways = (ll) rowDP[H][i] * colDP[W][j] % MOD;
            ways = ways * fact[spareRows - j + 1][spareRows] % MOD;
            ways = ways * fact[spareCols - i + 1][spareCols] % MOD;
            // cout << " = " << ways << endl;
            answer = (answer + ways) % MOD;
        }
    }
    cout << answer << endl;
    return 0;
}