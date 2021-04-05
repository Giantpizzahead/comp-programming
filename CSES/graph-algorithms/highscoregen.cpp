#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N = 2500;
struct Edge {
    int a, b, x;
};
vector<Edge> edges;

void gen() {
    edges.push_back({0, 0, 2});
    rep(i, 1, N) {
        edges.push_back({0, i, -2});
        edges.push_back({0, i, -1});
    }

    // edges.push_back({0, 0, 500});
    // rep(i, 1, N) {
    //     edges.push_back({0, i, 100});
    // }
    // rep(i, 1, 51) {
    //     rep(j, 0, 50) {
    //         edges.push_back({0, i, 101+j});
    //     }
    // }

    // rep(i, 1, N) {
    //     edges.push_back({0, i, 1});
    //     edges.push_back({i, 0, 1});
    // }
}

ofstream fout("input.txt");
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    gen();
    fout << N << " " << sz(edges) << '\n';
    rep(i, 0, sz(edges)) {
        fout << edges[i].a+1 << " " << edges[i].b+1 << " " << edges[i].x << '\n';
    }
    fout.close();
    return 0;
}