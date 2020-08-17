#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int arr[100000], numWithSum[3000005];
string str;

void solve() {
    cin >> N >> str;
    for (int i = 0; i < N; i++) arr[i] = str[i] - '0';
    for (int i = 1500000 - N * 11; i < 1500000 + N * 11; i++) numWithSum[i] = 0;

    long long answer = 0;
    int zeroLoc = 1500000;
    for (int i = 0; i < N; i++) {
        numWithSum[zeroLoc]++;
        zeroLoc++;
        zeroLoc -= arr[i];
        answer += numWithSum[zeroLoc];
    }
    cout << answer << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}