#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 100005;
int N;
ll arr[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    
    ll trailingPos = 0, answer = 0, overcount = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] > 0) trailingPos += arr[i];
        else {
            overcount += min(trailingPos, -arr[i]);
            trailingPos -= min(trailingPos, -arr[i]);
        }
        answer += abs(arr[i]);
    }
    answer /= 2;
    answer -= overcount;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}