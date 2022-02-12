/**
 * Solution: 
 * Runtime: O(2N * sqrt(4e5))
 */

#include "paint.h"

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
  // Generate color arrays
  vector<vector<int>> cToI(K);
  rep(i, 0, M) {
    rep(j, 0, A[i]) {
      cToI[B[i][j]].push_back(i);
      cToI[B[i][j]].push_back(i+M);
    }
  }
  // Offset the color arrays
  int numVals = 2*M+N;
  vector<int> lastNo(numVals, -2), lastUpd(numVals, -2);
  vector<bool> canUse(N);
  // Iterate
  rep(i, 0, N) {
    for (int j : cToI[C[i]]) {
      // Offset based on current index
      int x = j+(N-1-i);
      if (lastUpd[x] != i-1) {
        // Reset
        lastNo[x] = i-1;
      }
      if (lastNo[x] <= i-M) {
        // This range works
        canUse[i] = true;
      }
      lastUpd[x] = i;
    }
  }
  // Do greedy
  int ans = 0, lastUsed = -1, lastValid = -1;
  rep(i, 0, N-1) {
    if (canUse[i]) lastValid = i;
    if (lastUsed <= i-M) {
      if (lastValid == -1) {
        ans = -1;
        break;
      } else {
        ans++;
        lastUsed = lastValid;
        lastValid = -1;
      }
    }
  }
  if (ans != -1 && canUse[N-1]) ans++;
  else ans = -1;
  // rep(i, 0, N) cout << canUse[i] << " \n"[i==N-1];
  return ans;
}
