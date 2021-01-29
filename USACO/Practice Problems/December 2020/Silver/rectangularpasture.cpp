#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2500;

int N;
struct Cow {
    int x, y;
};
Cow cows[MAXN];

int numTopR[MAXN][MAXN], numTopL[MAXN][MAXN];

void solve() {
    cin >> N;
    vector<int> xCoords, yCoords;
    for (int i = 0; i < N; i++) {
        cin >> cows[i].x >> cows[i].y;
        xCoords.push_back(cows[i].x);
        yCoords.push_back(cows[i].y);
    }
    sort(xCoords.begin(), xCoords.end());
    sort(yCoords.begin(), yCoords.end());
    for (int i = 0; i < N; i++) {
        cows[i].x = distance(xCoords.begin(), lower_bound(xCoords.begin(), xCoords.end(), cows[i].x));
        cows[i].y = distance(yCoords.begin(), lower_bound(yCoords.begin(), yCoords.end(), cows[i].y));
    }
    sort(cows, cows+N, [](const Cow& a, const Cow& b) { return a.x < b.x; });

    for (int i = 0; i < N; i++) {
        numTopR[i][i] = 0;
        for (int j = i+1; j < N; j++) {
            numTopR[i][j] = numTopR[i][j-1];
            if (cows[j].y > cows[i].y) numTopR[i][j]++;
        }
    }

    for (int i = N-1; i >= 0; i--) {
        numTopL[i][i] = 0;
        for (int j = i-1; j >= 0; j--) {
            numTopL[i][j] = numTopL[i][j+1];
            if (cows[j].y > cows[i].y) numTopL[i][j]++;
        }
    }

    ll answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int top, bot;
            if (cows[i].y > cows[j].y) {
                top = numTopR[i][j];
                bot = j-i-1 - (numTopL[j][i]-1);
            } else if (cows[j].y > cows[i].y) {
                top = numTopL[j][i];
                bot = j-i-1 - (numTopR[i][j]-1);
            } else {
                top = 0;
                bot = 0;
            }
            // cout << i << " " << j << " = " << top << " " << bot << endl;
            answer += (top + 1) * (bot + 1);
        }
    }

    cout << answer + 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}