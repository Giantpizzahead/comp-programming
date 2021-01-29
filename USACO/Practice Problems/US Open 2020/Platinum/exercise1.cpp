/**
 * Exercise: Subtask 1
 */

#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned long long ll;
typedef __uint128_t L;
struct FastMod {
    ll b, m;
    FastMod(ll b) : b(b), m(ll((L(1) << 64) / b)) {}
    ll reduce(ll a) {
        ll q = (ll)((L(m) * a) >> 64);
        ll r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

const int MAXN = 7500;

int N, M;
int A[MAXN];
unordered_map<int, int> answer;
bool used[MAXN], vis[MAXN];

int gcf(int a, int b) {
    if (b == 0) return a;
    return gcf(b, a % b);
}

int lcm(int a, int b) {
    return a / gcf(a, b) * b;
}

void simArr() {
    for (int i = 0; i < N; i++) vis[i] = false;
    int currLCM = 1;
    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;
        int cycleLen = 0;
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            j = A[j];
            cycleLen++;
        }
        currLCM = lcm(cycleLen, currLCM);
    }
    answer[currLCM]++;
}

void genArrs(int i) {
    if (i == N) {
        simArr();
        return;
    }
    for (int j = 0; j < N; j++) {
        if (used[j]) continue;
        used[j] = true;
        A[i] = j;
        genArrs(i+1);
        used[j] = false;
    }
}

void solve() {
    genArrs(0);
    ll ans = 1;
    for (auto p : answer) {
        for (int i = 0; i < p.second; i++) {
            ans = F.reduce(ans * p.first);
        }
    }
    cout << ans << endl;
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    cin >> N >> M;
    F = FastMod(M);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}