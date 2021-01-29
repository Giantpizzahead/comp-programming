#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int N = 9, D = 12;
int trans1[] = {0, 1, 3, 4, 6, 7, 0, 1, 2, 3, 4, 5};
int trans2[] = {1, 2, 4, 5, 7, 8, 3, 4, 5, 6, 7, 8};
unordered_set<string> visited;
string str;

queue<string> q;
int currLeft, nextLeft, currCost;
void solve() {
    visited.reserve(370000);
    rep(i, 0, N) {
        char c;
        cin >> c;
        str += c;
    }

    visited.insert(str);
    q.push(str);
    currLeft++;
    while (!q.empty()) {
        string& s = q.front();
        if (currLeft == 0) {
            currLeft = nextLeft;
            nextLeft = 0;
            currCost++;
        }
        currLeft--;
        if (s == "123456789") {
            cout << currCost << '\n';
            return;
        }
        rep(i, 0, D) {
            string ns = s;
            swap(ns[trans1[i]], ns[trans2[i]]);
            if (visited.find(ns) != visited.end()) continue;
            visited.insert(ns);
            q.push(ns);
            nextLeft++;
        }
        q.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}