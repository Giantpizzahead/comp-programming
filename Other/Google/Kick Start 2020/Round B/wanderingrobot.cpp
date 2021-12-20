#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
using ll = long long;
const int MAXN = 2e5+10;

double fact[MAXN];

int W, H, L, U, R, D;
double probSoFar;

void evalDiag() {
    for (int i = 0; i < min(W-R-1, U-1); i++) {
        int totalDist = R-1+U-1;
        int numRight = R+i;
        // cout << "diag " << i << " " << totalDist << " " << numRight << endl;
        double currProb = fact[totalDist] - fact[totalDist - numRight] - fact[numRight] - totalDist;
        // cout << currProb << ": " << pow(2, currProb) << endl;
        probSoFar += pow(2, currProb);
    }
    if (U-1 >= W-R && W-R != 0) {
        // Eval corner (special case)
        for (int i = W-R-1; i < U-1; i++) {
            int totalDist = R-1+U-1;
            totalDist -= (i - (W-R-1)) + 1;
            int numRight = W-2;
            // cout << "special " << i << " " << totalDist << " " << numRight << endl;
            double currProb = fact[totalDist] - fact[totalDist - numRight] - fact[numRight] - totalDist - 1;
            // cout << currProb << ": " << pow(2, currProb) << endl;
            probSoFar += pow(2, currProb);
        }
    }
}

void solve() {
    cin >> W >> H >> L >> U >> R >> D;
    probSoFar = 0;
    // Top-right diag
    evalDiag();
    // Bot-left diag
    swap(W, H);
    swap(L, U);
    swap(R, D);
    evalDiag();
    cout << probSoFar << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(9);
    fact[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i-1] + log2(i);
    }
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}