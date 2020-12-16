#include <iostream>
#include <string>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
int cntA[26], cntB[26];
string A[MAXN];

void solve(int tn) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A+N, [](const string& a, const string& b) {
        for (int i = 0; i < 26; i++) {
            cntA[i] = 0;
            cntB[i] = 0;
        }
        for (int i = 0; i < a.length(); i++) cntA[a[i]-'a']++;
        for (int i = 0; i < b.length(); i++) cntB[b[i]-'a']++;
        for (int i = 0; i < 26; i++) {
            if (cntA[i] != cntB[i]) return cntA[i] > cntB[i];
        }
        return a < b;
    });

    cout << "Dictionary #" << tn << ":\n";
    for (int i = 0; i < N; i++) {
        cout << A[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}