/*
This is a linear time solution. It works for bounds N, M <= 5e5.

Solution: The general method is to try placing cows in the ordering, and simulating to check if the optimal answer is still attainable, backtracking if it's not. It's possible to do this "simulation" in constant time by keeping a running sum and max. It can also be proven that the optimal order starts with cows sorted from gang 1 to M, with the exception of at most 1 gang, and ends with cows from gang 1 (the ones left on the field at the end). This allows you to find the order by simulating at most 2*N+M cows.

Simulation - This process can be thought of as "pairing" cows from different gangs on the field. The general greedy idea is to always use the largest remaining gang first, so that you don't leave any big gang unpaired. This slow approach leads to a fast one using casework; if the largest gang (other than gang 1) is too big, then you'll have unpaired cows that take away from gang 1. Otherwise, parity decides the number of unpaired cows. The current cows on the field, along with their gang type (1 or not 1), need to be considered.

Optimal order - The optimal ordering ends with cows from gang 1, all of whom are left on the field at the end. (If they weren't at the end, they'd be paired away!) In addition, the optimal order starts with cows sorted from gang 1 to M, with the exception of at most 1 gang. The reason why we can't just use sorted cows is if one gang is too big, requiring it to be paired with all the other gangs in order to use all the cows. If we had more than one big gang, the one that comes later would "take care of" the earlier gang, so it's never optimal to have more than one gang out of sorted order.

Runtime: O(2*N+M)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

int N, M;
vector<int> A, order;

int stageI, stageC, prevStageI, prevStageC;

int prevSum, prevMax, currSum, currMax;
vector<int> numWithSize;

void useCow(int x) {
    // debug << "use " << x << endl;
    assert(A[x] != 0);
    A[x]--;
    order.push_back(x);
    prevStageI = stageI, prevStageC = stageC;
    prevSum = currSum, prevMax = currMax;
    if (x != 0) {
        numWithSize[A[x]+1]--;
        if (numWithSize[currMax] == 0) currMax--;
        numWithSize[A[x]]++;
        currSum--;
    }
    if (stageI == -1 || stageI == x) {
        stageI = x;
        stageC++;
    } else {
        stageC--;
        if (stageC == 0) stageI = -1;
    }
}

void backtrack() {
    // debug << "back" << endl;
    int x = order.back();
    order.pop_back();
    A[x]++;
    if (x != 0) {
        numWithSize[A[x]-1]--;
        numWithSize[A[x]]++;
    }
    stageI = prevStageI, stageC = prevStageC;
    currSum = prevSum, currMax = prevMax;
}

int findAns() {
    // Add to stage if needed
    int oldV;
    if (stageI > 0) {
        oldV = A[stageI];
        stageC += A[stageI];
        A[stageI] = 0;
        
    }

    // Calculate sum and current max
    int tempSum = currSum + stageC;
    if (stageI > 0) tempSum -= oldV;
    int tempMax = max(currMax, stageC);

    // Do casework
    int minUnpaired, res = -1;
    int sumExceptMax = tempSum - tempMax;
    if (sumExceptMax >= tempMax) {
        minUnpaired = tempSum % 2;
    } else if (stageI == 0 && tempMax == stageC) {
        // 1 is on stage, also most cows
        res = A[0] + (tempMax - sumExceptMax);
    } else {
        minUnpaired = tempMax - sumExceptMax;
    }

    if (res == -1) {
        if (A[0] <= minUnpaired) res = -1;
        else res = A[0] - minUnpaired;
    }
    // debug << "findAns = " << res << endl;

    // Revert stage changes
    if (stageI > 0) {
        stageC -= oldV;
        A[stageI] = oldV;
    }
    return res;
}

void solve() {
    cin >> N >> M;
    A.resize(M);
    rep(i, 0, M) cin >> A[i];
    stageI = -1, stageC = 0;

    // Initialize tracked values
    currSum = N - A[0];
    numWithSize.resize(N);
    currMax = -1;
    rep(i, 1, M) {
        currMax = max(A[i], currMax);
        numWithSize[A[i]]++;
    }

    int ans = findAns();
    if (ans <= 0) {
        cout << "NO\n";
        return;
    }

    // Generate order
    int reps = A[0] - ans;
    rep(i, 0, reps) useCow(0);
    int ci = 1, maxI = -1;
    while (ci != M) {
        if (A[ci] == 0) {
            ci++;
            continue; 
        }
        // Use smallest index cow
        useCow(ci);
        int curr = findAns();
        if (curr == ans) {
            // This works
            continue;
        }
        // This cow doesn't work; use the one max cow
        backtrack();
        if (maxI == -1) {
            // Find the one max cow
            rep(j, ci+1, M) {
                useCow(j);
                curr = findAns();
                if (curr == ans) {
                    // This works
                    maxI = j;
                    break;
                }
                backtrack();
            }
            assert(maxI != -1);
        } else {
            useCow(maxI);
            assert(findAns() == ans);
        }
    }
    // Add final cows
    rep(i, 0, ans) useCow(0);

    cout << "YES\n";
    cout << ans << '\n';
    for (int x : order) cout << x+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    solve();
    return 0;
}