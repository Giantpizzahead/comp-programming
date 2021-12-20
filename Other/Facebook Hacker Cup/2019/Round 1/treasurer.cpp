#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MOD = 1000000007;
const int MAXN = 1000000;

int N, K;
int pow2[MAXN];
char V[MAXN];

void solve(int tn) {
    fin >> N >> K;
    string str;
    fin >> str;
    for (int i = 0; i < N; i++) V[i] = str[i];

    int cost = 0, maxB = 0;
    for (int i = N-1; i >= 0; i--) {
        if (V[i] == 'B') maxB++;
        else maxB--;

        if (maxB > K) {
            // Must change this student's vote
            cost = (cost + pow2[i]) % MOD;
            maxB -= 2;
        }
        maxB = max(maxB, 0);
    }
    fout << "Case #" << tn << ": " << cost << endl;
}

int main() {
    pow2[0] = 2;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
    }
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}