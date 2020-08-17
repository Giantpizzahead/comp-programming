#include <iostream>

using namespace std;

int N;
bool used[200001];

int main() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int x;
        cin >> x;
        used[x] = true;
    }
    for (int i = 1; i <= N; i++) {
        if (!used[i]) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}