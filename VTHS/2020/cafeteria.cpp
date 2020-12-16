#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int A[10][2], answer;
int ratios[3][2], gcf[201][201];
int used[4];
unordered_set<ll> tested;

int genGCF(int a, int b) {
    if (a == 0) return b;
    else return genGCF(b%a, a);
}

inline ll hashRatios() {
    ll hash = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            hash *= 201;
            hash += ratios[i][j];
        }
    }
    return hash;
}

void fillRatio(int R) {
    if (R == 0) {
        // Either 0 or 1 will have value in between 1 to 200
        int table = used[0];
        for (int j = 1; j <= 200; j++) {
            ratios[0][0] = A[table*2][0];
            ratios[0][1] = j;
            int gcd = gcf[ratios[0][0]][ratios[0][1]];
            ratios[0][0] /= gcd;
            ratios[0][1] /= gcd;
            fillRatio(1);
            ratios[0][0] = 0;
            ratios[0][1] = 0;
        }
        table = used[1];
        for (int j = 1; j <= 200; j++) {
            ratios[0][0] = j;
            ratios[0][1] = A[table*2+1][0];
            int gcd = gcf[ratios[0][0]][ratios[0][1]];
            ratios[0][0] /= gcd;
            ratios[0][1] /= gcd;
            fillRatio(1);
            ratios[0][0] = 0;
            ratios[0][1] = 0;
        }
    } else if (R == 1) {
        // Either 1 or 2 will have value in between 1 to 200
        int table = used[1];
        for (int j = 1; j <= 200; j++) {
            ratios[1][0] = A[table*2+1][0];
            ratios[1][1] = j;
            int gcd = gcf[ratios[1][0]][ratios[1][1]];
            ratios[1][0] /= gcd;
            ratios[1][1] /= gcd;
            fillRatio(2);
            ratios[1][0] = 0;
            ratios[1][1] = 0;
        }
        table = used[2];
        for (int j = 1; j <= 200; j++) {
            ratios[1][0] = j;
            ratios[1][1] = A[table*2][1];
            int gcd = gcf[ratios[1][0]][ratios[1][1]];
            ratios[1][0] /= gcd;
            ratios[1][1] /= gcd;
            fillRatio(2);
            ratios[1][0] = 0;
            ratios[1][1] = 0;
        }
    } else if (R == 2) {
        // Either 2 or 3 will have value in between 1 to 200
        int table = used[2];
        for (int j = 1; j <= 200; j++) {
            ratios[2][0] = A[table*2][1];
            ratios[2][1] = j;
            int gcd = gcf[ratios[2][0]][ratios[2][1]];
            ratios[2][0] /= gcd;
            ratios[2][1] /= gcd;
            fillRatio(3);
            ratios[2][0] = 0;
            ratios[2][1] = 0;
        }
        table = used[3];
        for (int j = 1; j <= 200; j++) {
            ratios[2][0] = j;
            ratios[2][1] = A[table*2+1][1];
            int gcd = gcf[ratios[2][0]][ratios[2][1]];
            ratios[2][0] /= gcd;
            ratios[2][1] /= gcd;
            fillRatio(3);
            ratios[2][0] = 0;
            ratios[2][1] = 0;
        }
    } else {
        // See if this ratio works
        bool works = true;
        for (int i = 0; i < 5; i++) {
            int a, b, c, d;
            if (A[i*2][0] != -1) {
                a = A[i*2][0];
                b = a * ratios[0][1] / ratios[0][0];
                c = b * ratios[1][1] / ratios[1][0];
                d = c * ratios[2][1] / ratios[2][0];
            } else if (A[i*2+1][0] != -1) {
                b = A[i*2+1][0];
                c = b * ratios[1][1] / ratios[1][0];
                d = c * ratios[2][1] / ratios[2][0];
                a = b * ratios[0][0] / ratios[0][1];
            } else if (A[i*2][1] != -1) {
                c = A[i*2][1];
                d = c * ratios[2][1] / ratios[2][0];
                b = c * ratios[1][0] / ratios[1][1];
                a = b * ratios[0][0] / ratios[0][1];
            } else {
                d = A[i*2+1][1];
                c = d * ratios[2][0] / ratios[2][1];
                b = c * ratios[1][0] / ratios[1][1];
                a = b * ratios[0][0] / ratios[0][1];
            }
            if (A[i*2][0] != -1) a = A[i*2][0];
            if (A[i*2+1][0] != -1) b = A[i*2+1][0];
            if (A[i*2][1] != -1) c = A[i*2][1];
            if (A[i*2+1][1] != -1) d = A[i*2+1][1];
            if (a * ratios[0][1] != b * ratios[0][0] || b * ratios[1][1] != c * ratios[1][0] || c * ratios[2][1] != d * ratios[2][0]) {
                works = false;
                break;
            }
        }
        if (works) {
            ll hash = hashRatios();
            if (tested.find(hash) != tested.end()) return;
            tested.insert(hash);
            answer++;
            // cout << "ratio " << ratios[0][0] << " " << ratios[0][1] << " " << ratios[1][0] << " " << ratios[1][1] << " " << ratios[2][0] << " " << ratios[2][1] << endl;
        }
    }
}

void solve() {
    for (int i = 1; i <= 200; i++) {
        for (int j = 1; j <= 200; j++) {
            gcf[i][j] = genGCF(i, j);
        }
    }
    string str;
    for (int i = 0; i < 10; i++) {
        cin >> str;
        if (str == "_") A[i][0] = -1;
        else A[i][0] = stoi(str);
    }
    for (int i = 0; i < 10; i++) {
        cin >> str;
        if (str == "_") A[i][1] = -1;
        else A[i][1] = stoi(str);
    }

    // Check for empty tables
    for (int i = 0; i < 5; i++) {
        if (A[i*2][0] == -1 && A[i*2+1][0] == -1 && A[i*2][1] == -1 && A[i*2+1][1] == -1) {
            cout << "many" << endl;
            return;
        }
    }

    // Check for unused spots
    for (int i = 0; i < 4; i++) used[i] = -1;
    for (int i = 0; i < 5; i++) {
        if (A[i*2][0] != -1) used[0] = i;
        if (A[i*2+1][0] != -1) used[1] = i;
        if (A[i*2][1] != -1) used[2] = i;
        if (A[i*2+1][1] != -1) used[3] = i;
    }
    if (used[0] == -1 || used[1] == -1 || used[2] == -1 || used[3] == -1) {
        cout << "many" << endl;
        return;
    }

    // Every table has at least one filled spot, and all 4 spots have at least 1 value; start filling ratios
    fillRatio(0);

    cout << answer << endl;
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