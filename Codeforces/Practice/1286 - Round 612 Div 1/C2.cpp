#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

// 11111111   12222221     12333321
// 11111110   1222221[1]   12333210
// 12333321

const int C = 26, MAXN = 105;
int N;
vector<string> S[MAXN], T[MAXN];

string getRange(int l, int r) {
    if (l == r) {
        cout << "? " << l << " " << r << endl;
        string str; cin >> str;
        return str;
    } else if (l > r) return "";
    
    cout << "? " << l << " " << r << endl;
    int n = r-l+1;
    rep(i, 0, n*(n+1)/2) {
        string str; cin >> str;
        S[sz(str)].push_back(str);
    }
    cout << "? " << l+1 << " " << r << endl;
    n = r-l;
    rep(i, 0, n*(n+1)/2) {
        string str; cin >> str;
        T[sz(str)].push_back(str);
    }
    
    // Find the string one character at a time
    n = r-l+1;
    string ans = "";
    rep(i, 0, n) {
        int cnt1[C], cnt2[C];
        rep(j, 0, C) cnt1[j] = cnt2[j] = 0;
        for (string& str : S[i+1]) {
            for (char c : str) cnt1[c-'a']++;
        }
        for (string& str : T[i+1]) {
            for (char c : str) cnt2[c-'a']++;
        }
        for (char c : ans) cnt2[c-'a']++;
        // Find the character that does not match counts
        rep(j, 0, C) {
            if (cnt1[j] != cnt2[j]) {
                ans += j + 'a';
                break;
            }
        }
        S[i+1].clear();
        T[i+1].clear();
    }
    return ans;
}

void solve() {
    cin >> N;
    string left = getRange(1, N/2);
    cout << "? " << 1 << " " << N << endl;
    rep(i, 0, N*(N+1)/2) {
        string str; cin >> str;
        S[sz(str)].push_back(str);
    }
    string right = "";
    for (int i = N; i > (N+1)/2; i--) {
        // Reversed one-index
        int s = N+1-i;
        int cnt[C];
        rep(j, 0, C) cnt[j] = 0;
        for (string& str : S[s+1]) {
            for (char c : str) cnt[c-'a']++;
        }
        // Add extra characters at front and back
        rep(j, 0, s) cnt[left[j]-'a'] += s-j;
        rep(j, 0, s-1) cnt[right[j]-'a'] += s-j;
        // Find character with target modulo
        rep(j, 0, C) {
            if (cnt[j] % (s+1) != 0) {
                right += j + 'a';
                break;
            }
        }
    }
    reverse(all(right));
    if (N % 2 == 1) {
        // Find last character
        int cnt[C];
        rep(j, 0, C) cnt[j] = 0;
        for (char c : S[N][0]) cnt[c-'a']++;
        for (char c : left) cnt[c-'a']--;
        for (char c : right) cnt[c-'a']--;
        rep(j, 0, C) {
            if (cnt[j] != 0) {
                left += j + 'a';
                break;
            }
        }
    }
    cout << "! " << left << right << endl;
}

int main() {
    solve();
    return 0;
}