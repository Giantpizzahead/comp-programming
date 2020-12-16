#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
using ll = long long;
const int MAXN = 50000;

int N;
ll answer;
ll X[MAXN], L[MAXN], R[MAXN];

ll closestX;
multiset<pair<ll, ll>> pToRemove;
multiset<ll> activeP;
void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> X[i];
    sort(X, X+N);

    // Determine L
    L[0] = -1;
    closestX = X[0];
    for (int i = 1; i < N; i++) {
        // Remove all expired locs
        while (!pToRemove.empty() && pToRemove.begin()->first <= X[i]) {
            auto p = pToRemove.begin();
            activeP.erase(activeP.find(p->second));
            pToRemove.erase(p);
            closestX = max(p->first - p->second, closestX);
        }
        // Calculate L for current loc
        L[i] = X[i] - closestX;
        if (!activeP.empty()) L[i] = min(*activeP.begin(), L[i]);
        // Add new loc
        pToRemove.emplace(X[i] + L[i] + 1, L[i] + 1);
        activeP.insert(L[i] + 1);
    }

    // Determine R
    pToRemove.clear();
    activeP.clear();
    R[N-1] = -1;
    closestX = -X[N-1];
    for (int i = N-2; i >= 0; i--) {
        // Remove all expired locs
        while (!pToRemove.empty() && pToRemove.begin()->first <= -X[i]) {
            auto p = pToRemove.begin();
            activeP.erase(activeP.find(p->second));
            pToRemove.erase(p);
            closestX = max(p->first - p->second, closestX);
        }
        // Calculate L for current loc
        R[i] = -X[i] - closestX;
        if (!activeP.empty()) R[i] = min(*activeP.begin(), R[i]);
        // Add new loc
        pToRemove.emplace(-X[i] + R[i] + 1, R[i] + 1);
        activeP.insert(R[i] + 1);
    }

    // for (int i = 0; i < N; i++) cout << L[i] << ' ';
    // cout << endl;
    // for (int i = 0; i < N; i++) cout << R[i] << ' ';
    // cout << endl;

    // Try all cow placements
    pToRemove.clear();
    activeP.clear();
    answer = INT32_MAX;
    closestX = X[0];
    for (int i = 1; i < N; i++) {
        // Remove all expired locs
        while (!pToRemove.empty() && pToRemove.begin()->first <= X[i]) {
            auto p = pToRemove.begin();
            activeP.erase(activeP.find(p->second));
            pToRemove.erase(p);
            // cout << p->first - p->second << " transfer" << endl;
            closestX = max(p->first - p->second, closestX);
        }
        // Add new loc
        pToRemove.emplace(X[i] + (L[i] + 1) * 2, (L[i] + 1) * 2);
        activeP.insert((L[i] + 1) * 2);
        // Calculate L for current loc
        ll currVal = X[i] - closestX;
        if (!activeP.empty()) currVal = min(*activeP.begin(), currVal);
        currVal = max((R[i] + 1) * 2, currVal);
        // cout << i << " = " << currVal << endl;
        answer = min(currVal, answer);
    }

    cout << answer / 2 << "." << (answer % 2 == 1 ? "5" : "0") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}