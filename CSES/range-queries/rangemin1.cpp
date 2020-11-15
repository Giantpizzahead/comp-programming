#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>
using namespace std;

const int LOGN = 18;
const int MAXN = 200005;
const int INF = 1098765432;
int N, Q;
int arr[MAXN], sparse[LOGN][MAXN];



int getMin(int a, int b) {
    int bit = 31 - __builtin_clz(b-a+1);
    return min(sparse[bit][a], sparse[bit][b + 1 - (1 << bit)]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        sparse[0][i] = arr[i];
    }
    for (int i = 1; i < LOGN; i++) {
        for (int j = 0; j < N; j++) {
            int nextI = j + (1 << (i-1));
            sparse[i][j] = min(sparse[i-1][j], nextI >= N ? INF : sparse[i-1][j + (1 << (i-1))]);
        }
    }
    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        a--;
        b--;
        cout << getMin(a, b) << '\n';
    }
    return 0;
}