#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M;
map<string, int> items;
set<string> currList;
vector<string> answer;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        currList.clear();
        for (int j = 0; j < M; j++) {
            string str;
            cin >> str;
            if (currList.find(str) != currList.end()) continue;
            currList.insert(str);
            items[str]++;
        }
    }
    for (auto p : items) {
        if (p.second == N) answer.push_back(p.first);
    }
    cout << answer.size() << '\n';
    for (string& s : answer) cout << s << '\n';
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