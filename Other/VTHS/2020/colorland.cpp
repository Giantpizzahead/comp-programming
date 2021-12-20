#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
vector<int> colors[6];

void solve() {
    cin >> N;
    string str;
    for (int i = 1; i <= N; i++) {
        cin >> str;
        if (str == "Blue") colors[0].push_back(i);
        if (str == "Orange") colors[1].push_back(i);
        if (str == "Pink") colors[2].push_back(i);
        if (str == "Green") colors[3].push_back(i);
        if (str == "Red") colors[4].push_back(i);
        if (str == "Yellow") colors[5].push_back(i);
    }
    int currLoc = 0, steps = 0;
    while (currLoc != N) {
        int maxLoc = currLoc;
        for (int i = 0; i < 6; i++) {
            auto ptr = upper_bound(colors[i].begin(), colors[i].end(), currLoc);
            if (ptr == colors[i].end()) continue;
            else maxLoc = max(*ptr, maxLoc);
        }
        currLoc = maxLoc;
        steps++;
    }
    cout << steps << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}