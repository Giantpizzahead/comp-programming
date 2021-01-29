#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e6;

int N;
int lps[MAXN];
string str;

vector<int> periods;

void solve() {
    cin >> str;
    N = str.size();
    lps[0] = -1;
    int currLPS = -1;
    for (int i = 1; i < N; i++) {
        while (currLPS != -1 && str[currLPS+1] != str[i]) currLPS = lps[currLPS];
        if (str[currLPS+1] == str[i]) currLPS++;
        lps[i] = currLPS;
    }

    while (currLPS != -1) {
        periods.push_back(N-1-currLPS);
        currLPS = lps[currLPS];
    }
    periods.push_back(N);

    for (int i = 0; i < periods.size(); i++) {
        if (i != 0) cout << ' ';
        cout << periods[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}