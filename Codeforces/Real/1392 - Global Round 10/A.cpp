#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;

int N;
int arr[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    
    bool allSame = true;
    for (int i = 1; i < N; i++) {
        if (arr[i] != arr[i-1]) {
            allSame = false;
            break;
        }
    }

    if (allSame) cout << N << endl;
    else cout << 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}