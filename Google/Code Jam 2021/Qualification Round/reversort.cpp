#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> L;

void reverse(int i, int j) {
    int m = (j-i+1)/2;
    for (int k = 0; k < m; k++) {
        swap(L[i+k], L[j-k]);
    }
}

int reversort() {
    int cost = 0;
    for (int i = 0; i < N-1; i++) {
        int minPos = i;
        for (int j = i+1; j < N; j++) {
            if (L[j] < L[minPos]) minPos = j;
        }
        cost += minPos-i+1;
        reverse(i, minPos);
    }
    return cost;
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i+1 << ": ";
        cin >> N;
        L.resize(N);
        for (int j = 0; j < N; j++) cin >> L[j];
        cout << reversort() << endl;
    }
    return 0;
}