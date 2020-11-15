#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 200005;
int N, Q;
ll arr[MAXN], pre[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> arr[i];
    pre[0] = arr[0];
    for (int i = 1; i < N; i++) pre[i] = pre[i-1] + arr[i];
    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        a--;
        b--;
        cout << pre[b] - (a == 0 ? 0 : pre[a-1]) << '\n';
    }
    return 0;
}