#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXM = 9;

int M;
string words[MAXM];
string dp[1 << MAXM];

void solve(int tn) {
    fin >> M;
    for (int i = 0; i < M; i++) {
        fin >> words[i];
        dp[1 << i] = words[i];
    }

    for (int mask = 1; mask < (1 << M); mask++) {
        int numOneBits = 0;
        for (int i = 0; i < M; i++) {
            if (mask & (1 << i)) numOneBits++;
        }
        if (numOneBits == 1) continue;

        // Transition from each word
        vector<string> newStrs;
        for (int i = 0; i < M; i++) {
            if (mask & (1 << i)) {
                newStrs.push_back(dp[(mask & ~(1 << i))] + words[i]);
            }
        }

        // Find least lexicographical word
        string ans = newStrs[0];
        for (int i = 1; i < newStrs.size(); i++) {
            if (newStrs[i] < ans) ans = newStrs[i];
        }
        dp[mask] = ans;
    }

    fout << "Case #" << tn << ": " << dp[(1 << M) - 1] << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}