#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

int N, P;
int arr[MAXN];

bool checkWorks(int x) {
    for (int i = 0; i < N; i++) {
        if (arr[i] > x++) return false;
    }
    return true;
}

bool checkDivisible(int x) {
    int numChoices = 0, arrI = 0;
    for (int i = 0; i < N; i++) {
        while (arrI != N && arr[arrI] <= x) {
            numChoices++;
            arrI++;
        }
        if (numChoices == P) return true;
        numChoices--;
        x++;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> P;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr+N);

    // Find min x that works
    int low = 0, high = arr[N-1];
    while (low < high) {
        int mid = (low + high) / 2;
        if (checkWorks(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    int lowestWorks = low;

    // Find min x that is divisible by p
    low = lowestWorks, high = arr[N-1];
    while (low < high) {
        int mid = (low + high) / 2;
        if (checkDivisible(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    int lowestDivisible = low;

    // Print answer
    int answer = lowestDivisible - lowestWorks;
    cout << answer << '\n';
    for (int i = lowestWorks; i < lowestDivisible; i++) {
        if (i != lowestWorks) cout << ' ';
        cout << i;
    }
    cout << '\n';
    return 0;
}