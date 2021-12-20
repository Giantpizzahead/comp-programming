#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 10;
const double EPSILON = 1e-9;

int N, A[MAXN], B[MAXN], xs, ys, xt, yt;
double G, timeS, timeL;

struct State {
    double t, f;
    State(double t, double f) : t(t), f(f) {}

    bool operator<(const State& o) const {
        return t < o.t;
    }
};
set<State> S[MAXN][MAXN];

void addState(int x, int y, double t, double f) {
    // Only add if the state doesn't exist yet
    auto ptr = S[x][y].lower_bound({t-EPSILON, -1});
    if (ptr != S[x][y].end() && ptr->t < t+EPSILON) {
        // Already exists; keep the one with less fuel usage
        f = min(ptr->f, f);
        S[x][y].erase(ptr);
    }
    S[x][y].emplace(t, f);
}

void addStates(int x, int y, double t, double f, int l) {
    // Try all speed limits
    double nt, nf;
    for (int v = 5; v <= l; v += 5) {
        nt = t + G / v;
        nf = f + G / (80-0.03*v*v);
        addState(x, y, nt, nf);
    }
}

void solve() {
    cin >> N >> G;
    rep(i, 0, N) cin >> B[i];
    rep(i, 0, N) cin >> A[i];
    cin >> xs >> ys >> xt >> yt >> timeS >> timeL;
    timeS /= 60, timeL /= 60;
    xs--, ys--, xt--, yt--;

    // Make sure going towards top-right
    if ((xs < xt && ys > yt) || (xs > xt && ys < yt)) {
        // Flip
        rep(i, 0, N/2) swap(B[i], B[N-1-i]);
        ys = N-1-ys;
        yt = N-1-yt;
    }
    if (xs > xt && ys > yt) {
        swap(xs, xt);
        swap(ys, yt);
    }
    assert(xs <= xt && ys <= yt);

    // Spread from initial position
    S[xs][ys].emplace(0, 0);
    rep(x, xs, xt+1) {
        rep(y, ys, yt+1) {
            if (x == xt && y == yt) continue;
            debug << "on " << x << " " << y << ": " << sz(S[x][y]) << endl;
            for (const State& s : S[x][y]) {
                // debug << s.t << " " << s.f << endl;
                // Move up
                if (y != yt) {
                    addStates(x, y+1, s.t, s.f, A[x]);
                }
                // Move right
                if (x != xt) {
                    addStates(x+1, y, s.t, s.f, B[y]);
                }
            }
        }
    }

    State earliest(-1, -1);
    State fuel(-1, -1);
    for (const State& s : S[xt][yt]) {
        if (s.t < timeS-EPSILON || s.t > timeL+EPSILON) continue;
        // Record earliest (or least fuel)
        if (earliest.t < 0 || s.t < earliest.t) {
            earliest = s;
        } else if (abs(s.t - earliest.t) < EPSILON) {
            earliest.f = min(s.f, earliest.f);
        }
        // Record least fuel (or earliest)
        if (fuel.f < 0 || s.f < fuel.f) {
            fuel = s;
        } else if (abs(s.f - fuel.f) < EPSILON) {
            fuel.t = min(s.t, fuel.t);
        }
    }
    if (earliest.t < 0) cout << "IMPOSSIBLE\n";
    else {
        cout << fixed << setprecision(9);
        cout << "The earliest  arrival: " << earliest.t*60 << " minutes, fuel " << earliest.f << " gallons\n";
        cout << "The economical travel: " << fuel.t*60 << " minutes, fuel " << fuel.f << " gallons\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}