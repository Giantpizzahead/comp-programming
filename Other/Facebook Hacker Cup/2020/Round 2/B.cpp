#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using ld = long double;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 8005;

int N;
ld P;

// dp[i][j] = Expected # of matches with i people below, j people in tournament
ld dp[MAXN][MAXN];

void solve(int tn) {
    fin >> N >> P;

    dp[0][1] = 0;
    for (int j = 2; j <= N; j++) {
        for (int i = 0; i < j; i++) {
            ld probPlayerPicked = (ld) 2 / j;

            // If player picked...
            ld probBelow = (ld) i / (j-1);
            ld probAbove = (ld) (j-i-1) / (j-1);
            ld numFromPicked = dp[i][j-1] * probAbove * (1-P);
            if (i != 0) numFromPicked += dp[i-1][j-1] * probBelow * P;
            numFromPicked *= probPlayerPicked;

            // If player not picked...
            ll numPairs = (ll) j * (j-1) / 2;
            ll numFromBelow = (ll) i * (i-1) / 2;
            ll numFromAbove = (ll) (j-i-1) * (j-i-2) / 2;
            ll numFromBoth = (ll) i * (j-i-1);
            if (numFromAbove + numFromBelow + numFromBoth != numPairs - (j-1)) {
                cout << "ERROR" << endl;
            }
            ld probFromBelow = (ld) numFromBelow / numPairs;
            ld probFromAbove = (ld) numFromAbove / numPairs;
            ld probFromBoth = (ld) numFromBoth / numPairs;
            ld numFromNotPicked = dp[i][j-1] * probFromAbove + dp[i][j-1] * probFromBoth * (1-P);
            if (i != 0) {
                numFromNotPicked += dp[i-1][j-1] * probFromBelow + dp[i-1][j-1] * probFromBoth * P;
            }

            dp[i][j] = 1 + numFromPicked + numFromNotPicked;
        }
    }

    /*
    cout << "Case " << tn << "\n";
    for (int j = 1; j <= N; j++) {
        for (int i = 0; i < j; i++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
    */

    fout << "Case #" << tn << ":\n";
    for (int i = 0; i < N; i++) {
        fout << dp[i][N] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(8);
    fout << fixed << setprecision(8);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}