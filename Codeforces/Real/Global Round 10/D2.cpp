#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;
const int INF = 987654321;

int N;
string str;
int strNum[MAXN];

void solve() {
    cin >> N >> str;
    for (int i = 0; i < N; i++) strNum[i] = str[i] == 'R' ? 1 : 0;

    int answer = 0, lastNum = 2, inARow = 0;
    for (int i = 0; i < 3 * N; i++) {
        int ri = i % N;
        if (strNum[ri] == lastNum) {
            inARow++;
        } else {
            inARow = 1;
            lastNum = strNum[ri];
        }

        if (inARow == 3) {
            // Too many in a row; must switch one
            answer++;
            if (strNum[(ri+1)%N] != lastNum) {
                // Switch middle
                inARow = 1;
                strNum[ri == 0 ? N-1 : ri-1] = 1-strNum[ri == 0 ? N-1 : ri-1];
            } else {
                // Switch edge
                strNum[ri] = 1-strNum[ri];
                inARow = 1;
                lastNum = strNum[ri];
            }
        }
    }

    // for (int i = 0; i < N; i++) cout << (strNum[i] == 1 ? 'R' : 'L');
    // cout << endl;

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}