#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N;

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    ll answer = -1000000007, curr = 0;
    int x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        curr += x;
        answer = max(curr, answer);
        if (curr < 0) curr = 0;
    }
    cout << answer << endl;
}