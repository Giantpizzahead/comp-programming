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

ld probs[MAXN], matches[MAXN], probPre[MAXN];

void solve(int tn) {
    fin >> N >> P;
    for (int i = 0; i < N; i++) {
        probs[i] = 1;
        matches[i] = 0;
    }

    // Simulate rounds
    cout << fixed << setprecision(8);
    fout << fixed << setprecision(8);
    cout << "Case " << tn << endl;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            cout << probs[j] << ' ';
        }
        cout << endl;
        // Prefix sums
        probPre[0] = probs[0];
        for (int j = 1; j < N; j++) probPre[j] = probPre[j-1] + probs[j];

        // For each player
        for (int j = 0; j < N; j++) {
            matches[j] += probs[j];
            ld probPlayerPicked = probs[j] * 2 / (N - i);
            ld probFreePass = probs[j] - probPlayerPicked;
            // Will this player get eliminated?
            ld chanceBelow = (j == 0 ? 0 : probPre[j-1]);
            ld chanceAbove = probPre[N-1] - probPre[j];
            ld chanceTotal = chanceBelow + chanceAbove;
            ld probMatchPass = (chanceBelow * P + chanceAbove * (1 - P)) / chanceTotal;
            probs[j] = probFreePass + probPlayerPicked * probMatchPass;
        }
    }
    for (int j = 0; j < N; j++) {
        cout << probs[j] << ' ';
    }
    cout << endl;

    fout << "Case #" << tn << ":\n";
    for (int i = 0; i < N; i++) {
        fout << matches[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}