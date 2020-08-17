#include <iostream>

using namespace std;
using ll = long long;

ll N;

int main() {
    cin >> N;
    bool notFirst = false;
    while (true) {
        if (notFirst) cout << ' ';
        else notFirst = true;
        cout << N;
        if (N == 1) break;
        if (N % 2 == 0) N /= 2;
        else N = N * 3 + 1;
    }
    cout << endl;
    return 0;
}