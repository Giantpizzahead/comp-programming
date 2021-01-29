#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <vector>

using namespace std;

int N, K;
bool used[105];
int arr[105];
vector<int> usedList;

void solve(int tn) {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) used[i] = false;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        used[arr[i]] = true;
    }

    int numUsed = 0;
    usedList.clear();
    for (int i = 1; i <= N; i++) {
        if (used[i]) {
            numUsed++;
            usedList.push_back(i);
        }
    }

    if (numUsed > K) {
        cout << -1 << endl;
        return;
    }

    // Just do a cycle
    cout << N * K << endl;
    bool isFirst = true;
    for (int i = 0; i < N; i++) {
        // Filler
        for (int j = 0; j < K - numUsed; j++) {
            if (!isFirst) cout << ' ';
            else isFirst = false;
            cout << 1;
        }
        // Cycle
        for (int x : usedList) {
            if (!isFirst) cout << ' ';
            else isFirst = false;
            cout << x;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}