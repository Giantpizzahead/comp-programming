#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    if (N < 3) cout << -1 << endl;
    else {
        cout << "99 98 1";
        for (int i = 3; i < N; i++) {
            cout << " 1";
        }
        cout << endl;
    }
    return 0;
}