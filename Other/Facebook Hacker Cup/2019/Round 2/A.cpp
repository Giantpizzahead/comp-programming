#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

int N, M, K, A, B, R1, C1, R2, C2;

void output(bool possible, int tn) {
    fout << "Case #" << tn << ": " << (possible ? 'Y' : 'N') << endl;
}

void solve(int tn) {
    fin >> N >> M >> K >> A >> B;
    if (K == 1) {
        fin >> R1 >> C1;
        if (N == 1 || M == 1) {
            output(true, tn);
        } else {
            output(false, tn);
        }
    } else {
        fin >> R1 >> C1 >> R2 >> C2;
        if (N == 1 || M == 1) {
            output(true, tn);
        } else {
            int parityX = (A + B) % 2;
            int parity1 = (R1 + C1) % 2;
            int parity2 = (R2 + C2) % 2;
            if (parityX == parity1 && parity1 == parity2) output(true, tn);
            else output(false, tn);
        }
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