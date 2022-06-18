// https://open.kattis.com/problems/accessdenied

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int N;
string P;

int guess(string& pass) {
    cout << pass << endl;
    string res; getline(cin, res);
    int loc1 = res.find("(");
    int loc2 = res.find(" ms");
    if (loc1 == string::npos || loc2 == string::npos) exit(0);
    else return stoi(res.substr(loc1+1, loc2-loc1-1));
}

void solve() {
    N = 0;
    string curr = "";
    int lastTime = 0;
    int res;
    rep(i, 1, 21) {
        curr += "A";
        N++;
        res = guess(curr);
        if (res != 5) {
            // Correct length
            lastTime = res;
            break;
        }
    }

    // Find characters, one at a time
    rep(i, 0, N) {
        rep(d, 0, 62) {
            char c;
            if (d < 26) c = 'A' + d;
            else if (d < 52) c = 'a' + (d-26);
            else c = '0' + (d-52);
            curr[i] = c;
            res = guess(curr);
            if (res < lastTime) {
                // A was the right character
                P += 'A';
                curr[i] = 'A';
                break;
            } else if (res > lastTime) {
                // This is the right character
                P += c;
                lastTime = res;
                break;
            }
        }
    }
}

int main() {
    solve();
    return 0;
}