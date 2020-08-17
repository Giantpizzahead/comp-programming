#include <iostream>

using namespace std;

int N;
int arr[1000005];

int main() {
    cin >> N;
    if (N == 1) cout << 1 << endl;
    else if (N <= 3) cout << "NO SOLUTION" << endl;
    else {
        for (int i = 2; i <= N; i += 2) {
            if (i != 2) cout << ' ';
            cout << i;
        }
        for (int i = 1; i <= N; i += 2) {
            cout << ' ' << i;
        }
        cout << endl;
    }
    return 0;
}