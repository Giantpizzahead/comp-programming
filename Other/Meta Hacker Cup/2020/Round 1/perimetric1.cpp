#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const ll MOD = 1000000007;
const ll INF = 1000000007;
const int MAXN = 1000000;

int N;
ll W;
ll L[MAXN], H[MAXN];

void solve(int tn) {
    ll lastX = -INF;
    ll currP = 0, answer = 1;
    for (int i = 0; i < N; i++) {
        if (L[i] <= lastX + W) {
            // Overlaps with last house
            currP -= (W - (L[i] - lastX)) * 2;
            // Find highest height that overlaps with this house
            ll highestH = -INF;
            for (int j = i-1; j >= 0; j--) {
                if (L[i] > L[j] + W) break;  // This house does not overlap
                highestH = max(H[j], highestH);
            }
            if (highestH < H[i]) {
                // This house is higher
                currP -= highestH * 2;
            } else {
                // This house is lower
                currP -= H[i] * 2;
            }
        }
        currP += W * 2 + H[i] * 2;
        currP %= MOD;
        if (currP < 0) currP += MOD;
        lastX = L[i];
        answer = answer * currP % MOD;
        // cout << currP << endl;
    }
    fout << "Case #" << tn << ": " << answer << endl;
}

void parseInput(int tn) {
    int K;
    ll Al, Bl, Cl, Dl, Ah, Bh, Ch, Dh;
    fin >> N >> K >> W;
    for (int i = 0; i < K; i++) {
        fin >> L[i];
    }
    fin >> Al >> Bl >> Cl >> Dl;
    for (int i = 0; i < K; i++) {
        fin >> H[i];
    }
    fin >> Ah >> Bh >> Ch >> Dh;
    for (int i = K; i < N; i++) {
        L[i] = (Al * L[i-2] + Bl * L[i-1] + Cl) % Dl + 1;
        H[i] = (Ah * H[i-2] + Bh * H[i-1] + Ch) % Dh + 1;
    }
    /*
    for (int i = 0; i < N; i++) {
        cout << L[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << H[i] << ' ';
    }
    cout << endl;
    */
    // cout << "----" << endl;
    solve(tn);
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}