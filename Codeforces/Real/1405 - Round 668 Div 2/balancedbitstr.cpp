#include <iostream>

using namespace std;
using ll = long long;

const int MAXN = 300005;
int N, K;
char arr[MAXN];

void solve() {
    cin >> N >> K;
    cin.get();
    string str;
    cin >> str;
    for (int i = 0; i < N; i++) arr[i] = str[i];

    int numZero = 0, numOne = 0, reqZero = 0, reqOne = 0, numQuestion = 0;
    for (int i = 0; i < K; i++) {
        if (arr[i] == '?') numQuestion++;
        else if (arr[i] == '0') numZero++;
        else numOne++;
    }

    reqZero = K / 2 - numZero;
    reqOne = K / 2 - numOne;
    if (reqZero < 0 || reqOne < 0 || reqZero + reqOne != numQuestion) {
        // Bad
        cout << "NO\n";
        return;
    }

    // From here, just make sure there are no future conflicts
    for (int i = K; i < N; i++) {
        if (arr[i] == '?') {
            arr[i] = arr[i-K];
        } else if (arr[i-K] == '?') {
            arr[i-K] = arr[i];
            if (arr[i] == '0') {
                reqZero--;
            } else {
                reqOne--;
            }
            if (reqZero < 0 || reqOne < 0) {
                cout << "NO\n";
                return;
            }
        } else if (arr[i] != arr[i-K]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}