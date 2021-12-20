#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
#define cerr if (false) cout
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 55;

int T, N, Q;
struct Median {
    int a, b, c;
};
vector<Median> M;
vector<int> P;
int numFound;
int A[MAXN];

int queryMedian(int a, int b, int c) {
    cerr << "query " << a+1 << ' ' << b+1 << ' ' << c+1 << endl;
    cout << a+1 << ' ' << b+1 << ' ' << c+1 << endl;
    int m; cin >> m;
    cerr << "answer " << m << endl;
    if (m == -1) exit(0);
    m--;
    return m;
}

void solve() {
    numFound = -1;
    rep(i, 0, N) {
        A[i] = -1;
        P.push_back(i);
    }
    while (!P.empty()) {
        cerr << "potential:";
        for (int p : P) cerr << ' ' << p+1;
        cerr << endl;
        // Find possible
        while (sz(P) > 2) {
            int a = rand() % sz(P);
            int b;
            do {
                b = rand() % sz(P);
            } while (b == a);
            int c;
            do {
                c = rand() % sz(P);
            } while (c == a || c == b);
            a = P[a], b = P[b], c = P[c];
            int m = queryMedian(a, b, c);
            if (m == b) swap(a, b);
            if (m == c) swap(a, c);
            // Median cannot be on edge
            P.erase(remove(all(P), a), end(P));
            M.push_back({a, b, c});
            cerr << "removed " << a+1 << endl;
        }
        // Figure out which one is on the left
        if (numFound != -1) {
            int m = queryMedian(A[numFound], P[0], P[1]);
            assert(m != A[numFound]);
            if (m == P[0]) {
                A[numFound+1] = P[0];
                A[N-2-numFound] = P[1];
            } else {
                A[numFound+1] = P[1];
                A[N-2-numFound] = P[0];
            }
        } else {
            // Doesn't matter
            A[0] = P[0];
            A[N-1] = P[1];
        }
        cerr << "set " << P[0]+1 << " " << P[1]+1 << endl;
        // Reenter medians which might've been ruled out
        for (int i = 0; i < sz(M); i++) {
            if (M[i].b == P[0] || M[i].b == P[1] || M[i].c == P[0] || M[i].c == P[1]) {
                P.push_back(M[i].a);
                M.erase(begin(M)+i);
                i--;
            }
        }
        P.erase(begin(P));
        P.erase(begin(P));
        numFound++;
    }
    assert(M.empty());
    assert(P.empty());
    rep(i, 0, N) {
        cout << A[i]+1;
        if (i == N-1) cout << endl;
        else cout << ' ';
    }
    int ans; cin >> ans;
    if (ans == -1) exit(0);
}

int main() {
    cin >> T >> N >> Q;
    // srand(time(NULL));
    srand(1337);
    for (int i = 0; i < T; i++) solve();
    return 0;
}