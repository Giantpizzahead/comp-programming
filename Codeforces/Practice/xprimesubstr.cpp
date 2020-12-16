#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAXN = 1001;

int N;
ll X;
ll A[MAXN];
string str;

unordered_map<ll, int> memo[MAXN];

int doDP(int i, ll state) {
    auto ptr = memo[i].find(state);
    if (ptr != memo[i].end()) {
        // Already calculated
        return ptr->second;
    }

    // cout << "dp " << i << " " << state << " " << s << endl;
    if (i == N) {
        memo[i][state] = 0;
        return 0;
    }
    // Delete this character
    int dpVal = 1 + doDP(i+1, state);
    // Don't delete this character
    ll newState = state * 10 + A[i], genState = 0;
    // Remove any divisible subarrays
    ll currS = 0;
    for (; newState > 0; newState /= 10) {
        currS += newState % 10;
        if (currS == X) {
            // X-prime substring!!!
            break;
        } else if (currS > X) {
            // Over; remove extraneous digits
            break;
        } else if (X % currS == 0) {
            // Divisible; this cannot be part of an x-prime substring
            break;
        }
        genState = genState * 10 + newState % 10;
    }
    if (currS != X) {
        // No x-prime substring; can continue
        dpVal = min(doDP(i+1, genState), dpVal);
    }
    memo[i][state] = dpVal;
    return dpVal;
}

int main() {
    cin >> str >> X;
    N = str.length();
    for (int i = 0; i < N; i++) A[i] = str[i] - '0';
    doDP(0, 0);
    // for (auto x : memo) {
    //     cout << x.first % 1001 << ' ' << x.first / 1001 << ' ' << x.second << endl;
    // }
    // cout << memo.size() << endl;
    cout << memo[0][0] << endl;
    return 0;
}