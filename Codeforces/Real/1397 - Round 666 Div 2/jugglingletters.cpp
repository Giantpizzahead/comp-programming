#include <iostream>

using namespace std;

const int MAXC = 300;

int N;
int charCounts[MAXC];
string str;

void solve() {
    cin >> N;
    for (int i = 0; i < MAXC; i++) charCounts[i] = 0;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (char c : str) {
            charCounts[c]++;
        }
    }
    bool possible = true;
    for (int i = 0; i < MAXC; i++) {
        if (charCounts[i] % N != 0) {
            possible = false;
            break;
        }
    }
    cout << (possible ? "YES" : "NO") << '\n';
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}