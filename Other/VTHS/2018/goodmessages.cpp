#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int O, N;
string str;

// bool isBad() {
//     int vowels = 0, other = 0;
//     for (int j = 0; j < str.size(); j++) {
//         if (str[j] == 'a' || str[j] == 'e' || str[j] == 'i' || str[j] == 'o' || str[j] == 'u' || str[j] == 'y') vowels++;
//         else other++;
//     }
//     return vowels >= other;
// }

void solve() {
    cin >> O >> str >> N;
    int good = 0, bad = 0;
    for (int i = 0; i < N; i++) {
        int vowels = 0, other = 0;
        for (int j = 0; j < str.size(); j++) {
            str[j] = (str[j]-'a'+O)%26+'a';
            if (str[j] == 'a' || str[j] == 'e' || str[j] == 'i' || str[j] == 'o' || str[j] == 'u' || str[j] == 'y') vowels++;
            else other++;
        }
        if (vowels*2 >= other) bad++;
        else good++;
    }
    if (good > bad) cout << "Boris\n";
    else cout << "Colleague\n";
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