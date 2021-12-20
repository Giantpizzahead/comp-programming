#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> kmp(string& T, string& P) {
    // Gen LPS array
    int lps[P.length()];
    lps[0] = -1;
    int curr = -1;
    for (int i = 1; i < P.length(); i++) {
        while (curr != -1 && P[i] != P[curr+1]) curr = lps[curr];
        if (P[i] == P[curr+1]) curr++;
        lps[i] = curr;
    }
    // KMP algorithm
    vector<int> matches;
    curr = -1;
    for (int i = 0; i < T.length(); i++) {
        while (curr != -1 && T[i] != P[curr+1]) curr = lps[curr];
        if (T[i] == P[curr+1]) curr++;
        if (curr == P.length()-1) {
            matches.push_back(i-curr);
            curr = lps[curr];
        }
    }
    return matches;
}

int N;
string A, B;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A >> B;
        vector<int> matches = kmp(A, B);
        if (matches.empty()) cout << -1;
        else for (int j = 0; j < matches.size(); j++) {
            if (j != 0) cout << ' ';
            cout << matches[j] + 1;
        }
        cout << endl;
    }
    return 0;
}