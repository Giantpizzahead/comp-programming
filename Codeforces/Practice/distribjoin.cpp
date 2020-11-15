#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 100005;
const ll INF = 1e17;

int M, N;
ll A[MAXN], B[MAXN];
ll aSum, bSum;

int main() {
    ios::sync_with_stdio(false);
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
        cin >> A[i];
        aSum += A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
        bSum += B[i];
    }
    sort(A, A+M);
    sort(B, B+N);

    ll answer = INF;

    // Merge into database A
    ll aAnswer = bSum;
    for (int i = M-2; i >= 0; i--) {
        aAnswer += min(A[i], bSum);
    }
    answer = min(answer, aAnswer);

    // Merge into database B
    ll bAnswer = aSum;
    for (int i = N-2; i >= 0; i--) {
        bAnswer += min(B[i], aSum);
    }
    answer = min(answer, bAnswer);

    cout << answer << endl;
}