#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll N, answer;

int main() {
    cin >> N;
    for (int i = 1; i <= 60; i++) {
        answer += N / (1L << i) * (1L << (i-1));
        answer += max(N % (1L << i) + 1 - (1L << (i-1)), 0LL);
    }
    cout << answer << endl;
}