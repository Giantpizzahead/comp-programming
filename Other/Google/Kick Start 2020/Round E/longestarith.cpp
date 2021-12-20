#include <iostream>

using namespace std;

const int MAXN = 200005;

int N;
int arr[MAXN];

void solve(int tn) {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];

    int lastI = 0, currD = arr[1] - arr[0], answer = 0;
    for (int i = 1; i < N; i++) {
        if (arr[i] - arr[i-1] != currD) {
            // End of current sequence
            answer = max(i-lastI, answer);
            lastI = i-1;
            currD = arr[i] - arr[i-1];
        }
    }
    answer = max(N-lastI, answer);

    cout << "Case #" << tn << ": " << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}