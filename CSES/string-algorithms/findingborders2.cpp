#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e6+5;

int N;
string str;
int lps[MAXN];
vector<int> borders;

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
    // cout << "lps: ";
    // for (int i = 0; i < N; i++) cout << lps[i] << ' ';
    // cout << endl;

    while (currLPS != -1) {
        borders.push_back(currLPS + 1);
        currLPS = lps[currLPS];
    }
    reverse(borders.begin(), borders.end());

    bool first = true;
    for (int x : borders) {
        if (!first) cout << ' ';
        else first = false;
        cout << x;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}