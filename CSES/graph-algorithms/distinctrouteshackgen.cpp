#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

struct Edge {
    int a, b;
};
int N;
vector<int> nodes;
vector<Edge> edges;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

void genCase(int X) {
    // Make the 2 lines
    int lineLen = 3;
    edges.push_back({0, X+1});
    rep(i, 1, lineLen) {
        edges.push_back({i+X, i+1+X});
    }
    edges.push_back({0, lineLen+1+X});
    rep(i, 1, lineLen) {
        edges.push_back({lineLen+i+X, lineLen+i+1+X});
    }
    edges.push_back({lineLen+X, N-1});
    edges.push_back({lineLen*2+X, N-1});
    // Make cross edges
    rep(i, 0, lineLen) {
        rep(j, 0, lineLen) {
            edges.push_back({1+i+X, lineLen+1+j+X});
        }
    }
}

void solve() {
    srand(time(NULL));
    N = 500;
    rep(i, 0, N) nodes.push_back(i);
    // Gen a bunch of the same pattern
    int offset = 0;
    while (sz(edges) < 980) {
        genCase(offset);
        offset += 6;
    }
    // Shuffle to stop luck from getting AC
    random_shuffle(next(nodes.begin()), prev(nodes.end()));
    random_shuffle(all(edges));
    cout << sz(nodes) << ' ' << sz(edges) << '\n';
    rep(i, 0, sz(edges)) {
        cout << nodes[edges[i].a]+1 << ' ' << nodes[edges[i].b]+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}