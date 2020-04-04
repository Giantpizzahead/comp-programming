/*
ID: sunnyky1
LANG: C++
TASK: stamps

Solution: Standard Knapsack. Find the longest contiguous
range using <=K stamps after the knapsack.

Runtime: O(10000KN)
*/

#include <iostream>
#include <fstream>
#include <algorithm>

#define MAXN 50
#define MAXDP 2000001
#define INF 987654321

using namespace std;

int dp[MAXDP];
int stamps[MAXN];
int K, N;

int main() {
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    fin >> K >> N;
    
    for (int i = 0; i < N; i++) {
        fin >> stamps[i];
    }

    fin.close();

    // Do DP
    for (int i = 1; i < MAXDP; i++) dp[i] = INF;
    for (int i = 0; i < N; i++) {
        for (int j = stamps[i]; j < MAXDP; j++) {
            dp[j] = min(dp[j-stamps[i]] + 1, dp[j]);
        }
    }

    // Find longest contiguous sequence starting from 1
    int answer = 0;
    for (int i = 1; i < MAXDP; i++) {
        if (dp[i] > K) {
            answer = i - 1;
            break;
        }
    }

    fout << answer << endl;
    fout.close();
}