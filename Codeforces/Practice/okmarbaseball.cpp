#include <iostream>

using namespace std;

const int MAXN = 200005;

int T, N;
int arr[MAXN];

void solve(int tn) {
    cin >> N;
    bool alreadySorted = true;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        if (arr[i] != i+1) alreadySorted = false;
    }

    if (alreadySorted) {
        cout << 0 << '\n';
        return;
    }

    // Check if only prefix and suffix are in same positions
    int longestPre, longestSuff;
    for (int i = 0; i < N; i++) {
        if (arr[i] != i+1) {
            longestPre = i-1;
            break;
        }
    }
    for (int i = N-1; i >= 0; i--) {
        if (arr[i] != i+1) {
            longestSuff = i+1;
            break;
        }
    }

    // If anything in between, must take 2 tries
    for (int i = longestPre + 2; i <= longestSuff - 2; i++) {
        if (arr[i] == i+1) {
            cout << 2 << '\n';
            return;
        }
    }
    cout << 1 << '\n';
}

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) solve(i);
    return 0;
}