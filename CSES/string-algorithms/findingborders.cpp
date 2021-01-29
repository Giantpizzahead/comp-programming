#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int HASHES = 3;
const int MAXN = 1e6;

int hashMod[HASHES] = {1324132127, 1111111121, 986978929};
int hashBase[HASHES] = {157, 173, 139};
int hashPow[HASHES][MAXN];

int startH[HASHES], endH[HASHES];

int N;
string str;
vector<int> borders;

void solve() {
    cin >> str;
    N = str.size();
    for (int i = 0; i < HASHES; i++) {
        hashPow[i][0] = 1;
        for (int j = 1; j < N; j++) {
            hashPow[i][j] = (ll) hashPow[i][j-1] * hashBase[i] % hashMod[i];
        }
    }

    for (int i = 0; i < N-1; i++) {
        bool equal = true;
        for (int j = 0; j < HASHES; j++) {
            startH[j] = ((ll) startH[j] * hashBase[j] + str[i]) % hashMod[j];
            endH[j] = (endH[j] + (ll) str[N-1-i] * hashPow[j][i]) % hashMod[j];
            if (startH[j] != endH[j]) equal = false;
            // cout << startH[j] << " " << endH[j] << endl;
        }
        if (equal) borders.push_back(i+1);
    }

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