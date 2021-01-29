#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXN = 2e5;

int N;
int A[MAXN], cnt[MAXN];

void solve() {
    cin>>N;
    F0R(i,N) cin>>A[i];

    cnt[0] = 1;
    ll answer = 0;
    int currDiv = 0;
    F0R(i,N) {
        currDiv += A[i];
        currDiv %= N;
        if (currDiv < 0) currDiv += N;
        answer += cnt[currDiv];
        cnt[currDiv]++;
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}