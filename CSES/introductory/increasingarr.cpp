#include <iostream>

using namespace std;
using ll = long long;

int N;

int main() {
    cin >> N;
    ll answer = 0;
    int currMax = 0, x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        if (x < currMax) {
            answer += currMax - x;
        }
        currMax = max(currMax, x);
    }
    cout << answer << endl;
}