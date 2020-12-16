#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAXN = 1001;

int N, X;
string str;

unordered_map<ll, int> memo;

inline ll genHash(int i, string state) {
    return (state.length() == 0 ? 0 : stoll(state)) * 2937 + i;
}

int doDP(int i, string state) {
    ll hashed = genHash(i, state);
    auto ptr = memo.find(hashed);
    if (ptr != memo.end()) {
        // Already calculated
        return ptr->second;
    }

    // cout << "dp " << i << " " << state << " " << s << endl;
    if (i == N) return 0;
    // Delete this character
    int dpVal = 1 + doDP(i+1, state);
    // Don't delete this character
    string newState = state + str[i];
    // Remove any divisible subarrays
    int currS = 0;
    for (int j = newState.length()-1; j >= 0; j--) {
        currS += newState[j] - '0';
        if (currS == X) {
            // X-prime substring!!!
            break;
        } else if (currS > X) {
            // Over; remove extraneous digits
            newState = newState.substr(j+1);
            break;
        } else if (X % currS == 0) {
            // Divisible; this cannot be part of an x-prime substring
            newState = newState.substr(j+1);
            break;
        }
    }
    if (currS != X) {
        // No x-prime substring; can continue
        dpVal = min(doDP(i+1, newState), dpVal);
    }
    memo[hashed] = dpVal;
    return dpVal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> str >> X;
    N = str.length();
    doDP(0, "");
    // for (auto x : memo) {
    //     cout << x.first << ' ' << x.second << endl;
    // }
    ll hashed = genHash(0, "");
    cout << memo[hashed] << '\n';
    return 0;
}