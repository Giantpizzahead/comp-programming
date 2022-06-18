#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

void solve() {
    int N = 3;
    int M = 3;
    int C = 26;

    // Get the answer
    vector<int> charCnt(C);
    vector<vector<char>> answer(N, vector<char>(M));
    for (int i = 0; i < N; i++) {
        string currLine;
        cin >> currLine;
        for (int j = 0; j < M; j++) {
            answer[i][j] = currLine[j];
            charCnt[answer[i][j] - 'A']++;
        }
    }
    
    // Process the guess
    int numYellow = 0;
    int numGreen = 0;
    for (int i = 0; i < N; i++) {
        string currLine;
        cin >> currLine;
        for (int j = 0; j < M; j++) {
            char c = currLine[j];
            if (charCnt[c - 'A'] != 0) {
                charCnt[c - 'A']--;
                numYellow++;
            }
            if (answer[i][j] == c) {
                numGreen++;
                numYellow--;
            }
        }
    }

    cout << numGreen << '\n';
    cout << numYellow << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}