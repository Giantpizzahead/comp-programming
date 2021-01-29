#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
string str;
vector<int> ones;

void solve() {
    cin >> str;
    N = str.size();
    ones.clear();
    int numOnes = 0;
    for (int i = 0; i < N; i++) {
        if (str[i] == '1') numOnes++;
        else {
            ones.push_back(numOnes);
            numOnes = 0;
        }
    }
    ones.push_back(numOnes);
    sort(ones.begin(), ones.end(), greater<int>());
    int answer = 0;
    bool aliceTurn = true;
    for (int x : ones) {
        if (aliceTurn) answer += x;
        aliceTurn = !aliceTurn;
    }
    cout << answer << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}