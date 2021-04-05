#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXK = 5005, MAXN = 1e6+5;

int N;
ll answer = 0;
struct Factor {
    int n, c;
};
vector<Factor> F[MAXK];
int cntF[MAXK];
int P[MAXK], C[MAXK];
int A[MAXN];

vector<int> factorize(int x) {
    vector<int> fact;
    for (int i = 2; i*i <= x && x != 1; i++) {
        while (x % i == 0) {
            fact.push_back(i);
            x /= i;
        }
    }
    if (x != 1) fact.push_back(x);
    return fact;
}

int currIter = 0;
int toMove[MAXK], toMoveIter[MAXK];
bool avoid[MAXK];
vector<int> consider;
void moveAnswer() {
    currIter++;
    consider.clear();
    rep(i, 1, MAXK) {
        if (avoid[i]) continue;
        else if (F[i].empty()) {
            avoid[i] = true;
            continue;
        }
        int maxF = F[i].back().n;
        if (toMoveIter[maxF] != currIter) {
            toMoveIter[maxF] = currIter;
            toMove[maxF] = 0;
            consider.push_back(maxF);
        }
        toMove[maxF] += C[i];
    }
    // Go to highest count if >N/2 there
    if (consider.empty()) return;
    int bestLoc = consider[0];
    for (int c : consider) {
        if (toMove[c] > toMove[bestLoc]) bestLoc = c;
    }
    if (toMove[bestLoc] <= N/2) return;
    // Move here
    // cerr << "move " << bestLoc << endl;
    answer += N - 2 * toMove[bestLoc];
    rep(i, 1, MAXK) {
        if (avoid[i]) continue;
        else if (F[i].back().n != bestLoc) avoid[i] = true;
        else if (--F[i].back().c == 0) F[i].pop_back();
    }
    moveAnswer();
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        if (A[i] == 0) A[i] = 1;
        C[A[i]]++;
    }
    rep(i, 1, MAXK) {
        vector<int> fact = factorize(i);
        for (int x : fact) P[x]++;
        rep(j, 1, i+1) {
            if (P[j] != 0) F[i].push_back({j, P[j]});
        }
    }
    // rep(i, 1, 10) {
    //     cout << i << ": ";
    //     for (auto& f : F[i]) rep(j, 0, f.c) cout << f.n << ' ';
    //     cout << endl;
    // }

    // Calc initial answer (placing samples at 1)
    rep(i, 1, MAXK) {
        if (C[i] == 0) continue;
        ll cnt = 0;
        for (auto& f : F[i]) cnt += f.c;
        cntF[i] = cnt;
        // cerr << i << ": " << cnt << endl;
        answer += cnt * C[i];
    }
    // cerr << "initial: " << answer << endl;
    
    // Move to better location
    moveAnswer();
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}