/*
The telephone number of the caller and the called number in record n are Caller(n) = S2n-1 and Called(n) = S2n where S1,2,3,... come from the "Lagged Fibonacci Generator":

For 1 ≤ k ≤ 55, Sk = [100003 - 200003k + 300007k3] (modulo 1000000)
For 56 ≤ k, Sk = [Sk-24 + Sk-55] (modulo 1000000)

If Caller(n) = Called(n) then the user is assumed to have misdialled and the call fails; otherwise the call is successful.

From the start of the records, we say that any pair of users X and Y are friends if X calls Y or vice-versa. Similarly, X is a friend of a friend of Z if X is a friend of Y and Y is a friend of Z; and so on for longer chains.

The Prime Minister's phone number is 524287. After how many successful calls, not counting misdials, will 99% of the users (including the PM) be a friend, or a friend of a friend etc., of the Prime Minister?
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int N = 1000000;
const int M = 990000;
const int P = 524287;

vector<ll> nums;

ll genNumber(ll n) {
  if (n <= 55) {
    nums.push_back((100003 - 200003 * n + 300007 * n*n*n) % N);
  } else {
    int s = sz(nums);
    nums.push_back((nums[s-24] + nums[s-55]) % N);
  }
  return nums.back();
}

struct DisjointSet {
  int P[N+1], S[N+1];

  DisjointSet() {
    rep(i, 0, N+1) {
      P[i] = -1;
      S[i] = 1;
    }
  }
  
  int find(int x) {
    if (P[x] == -1) return x;
    else {
      int r = find(P[x]);
      P[x] = r;
      return r;
    }
  }

  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return a;
    else if (S[a] > S[b]) {
      S[a] += S[b];
      S[b] = 0;
      P[b] = a;
      return a;
    } else {
      S[b] += S[a];
      S[a] = 0;
      P[a] = b;
      return b;
    }
  }
} ds;

void solve() {
  int round = 0, dials = 0;
  while (true) {
    round++;
    int a = genNumber(round*2-1);
    int b = genNumber(round*2);
    if (a == b) continue;
    else ds.merge(a, b);
    dials++;
    if (ds.S[ds.find(P)] >= M) {
      cout << dials << endl;
      return;
    }
  }
}

int main() {
    ios::sync_with_stdio(0);
    solve();
    return 0;
}