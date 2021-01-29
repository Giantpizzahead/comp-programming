#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXC = 1e6+5;
const int MAXN = 3e5+5;

int compN = 0;
int prime[MAXC];
int compID[MAXC];

struct DisjointSet {
    int V[MAXC], S[MAXC];

    DisjointSet() {
        rep(i, 0, MAXC) {
            V[i] = -1;
            S[i] = 1;
        }
    }

    void merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        else if (S[a] > S[b]) {
            S[a] += S[b];
            S[b] = 0;
            V[b] = a;
        } else {
            S[b] += S[a];
            S[a] = 0;
            V[a] = b;
        }
    }

    int find(int n) {
        if (V[n] == -1) return n;
        int res = find(V[n]);
        V[n] = res;
        return res;
    }
};
DisjointSet ds;

vi tempFact;
void compEdges(int n) {
    vector<int> fact;
    int temp = n;
    tempFact.clear();
    while (temp != 1) {
        tempFact.push_back(prime[temp]);
        temp /= prime[temp];
    }
    for (int x : tempFact) {
        // Go down here
        int newN = n / x;
        if (newN % x != 0) continue;
        newN /= x;
        // cout << "edge " << n << " -> " << newN << endl;
        ds.merge(newN, n);
    }
}

void precalc() {
    prime[1] = 1;
    rep(i, 2, MAXC) {
        if (prime[i] == 0) {
            prime[i] = i;
            for (int j = i+i; j < MAXC; j += i) prime[j] = i;
        }
        // cout << prime[i] << ' ';
    }
    // cout << endl;

    for (int i = 1; i < MAXC; i++) {
        compEdges(i);
    }
    rep(i, 1, MAXC) {
        compID[i] = ds.find(i);
    }

    // rep(i, 1, MAXC) cout << i << ": " << compID[i] << endl;
    // cout << endl;
}

int N, Q, ans1, ans2;
int A[MAXN];
vi comps[MAXC];
unordered_set<int> usedComps;
unordered_map<int, int> factors;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        comps[compID[A[i]]].push_back(i);
        usedComps.insert(compID[A[i]]);
    }
    // Answer for first second
    ans1 = 0;
    for (int c : usedComps) {
        // cout << "used " << comps[c].size() << endl;
        ans1 = max((int) comps[c].size(), ans1);
    }
    // cout << "first: ";
    // rep(i, 0, N) cout << A[i] << ' ';
    // cout << endl;

    // Update to next second
    for (int c : usedComps) {
        if (comps[c].size() % 2 == 1) continue;
        // Even-sized comp, all odd factors change to even
        int a = A[comps[c][0]];
        factors.clear();
        while (a != 1) {
            factors[prime[a]]++;
            a /= prime[a];
        }
        for (auto p : factors) {
            if (p.second % 2 == 0) continue;
            // Make this factor even
            for (int i : comps[c]) A[i] /= p.first;
        }
    }
    for (int c : usedComps) comps[c].clear();
    usedComps.clear();

    // cout << "two: ";
    // rep(i, 0, N) cout << A[i] << ' ';
    // cout << endl;

    // Calc answer for this second
    rep(i, 0, N) {
        comps[compID[A[i]]].push_back(i);
        usedComps.insert(compID[A[i]]);
    }
    ans2 = 0;
    for (int c : usedComps) {
        // cout << "used " << comps[c].size() << endl;
        ans2 = max((int) comps[c].size(), ans2);
        comps[c].clear();
    }
    usedComps.clear();

    // Queries
    cin >> Q;
    rep(i, 0, Q) {
        ll w; cin >> w;
        if (w == 0) cout << ans1 << '\n';
        else cout << ans2 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    precalc();
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}