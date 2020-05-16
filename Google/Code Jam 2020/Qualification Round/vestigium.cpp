#include <iostream>
#include <unordered_set>

using namespace std;

void solve(int tn) {
    int N;
    cin >> N;
    int arr[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    int trace = 0;
    for (int i = 0; i < N; i++) trace += arr[i][i];

    int numRows = 0;
    for (int i = 0; i < N; i++) {
        unordered_set<int> seen;
        bool noRepeats = true;
        for (int j = 0; j < N; j++) {
            if (seen.count(arr[i][j]) != 0) {
                noRepeats = false;
                break;
            } else seen.insert(arr[i][j]);
        }
        numRows += noRepeats ? 0 : 1;
    }

    int numCols = 0;
    for (int j = 0; j < N; j++) {
        unordered_set<int> seen;
        bool noRepeats = true;
        for (int i = 0; i < N; i++) {
            if (seen.count(arr[i][j]) != 0) {
                noRepeats = false;
                break;
            } else seen.insert(arr[i][j]);
        }
        numCols += noRepeats ? 0 : 1;
    }

    printf("Case #%d: %d %d %d\n", tn, trace, numRows, numCols);
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return EXIT_SUCCESS;
}
