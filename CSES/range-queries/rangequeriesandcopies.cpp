#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q, version, K;

struct Node {
    ll v;
    Node* l = nullptr;
    Node* r = nullptr;

    Node(ll v) : v(v) {}

    Node(const Node& n) : v(n.v), l(n.l), r(n.r) {}

    void merge() {
        v = l->v + r->v;
    }

    Node* init(int lb, int ub) {
        if (lb != ub) {
            l = new Node(0);
            l->init(lb, (lb+ub)/2);
            r = new Node(0);
            r->init((lb+ub)/2+1, ub);
        }
        return this;
    }

    Node* update(int i, int v, int lb, int ub) {
        if (lb == ub) {
            return new Node(v);
        }
        Node* n = new Node(*this);
        if (i > (lb+ub)/2) n->r = n->r->update(i, v, (lb+ub)/2+1, ub);
        else n->l = n->l->update(i, v, lb, (lb+ub)/2);
        n->merge();
        return n;
    }

    ll query(int l, int r, int lb, int ub) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return v;
        return this->l->query(l, r, lb, (lb+ub)/2) + this->r->query(l, r, (lb+ub)/2+1, ub);
    }
};

int currVersion[MAXN];
Node* segt[MAXN];

void solve() {
    cin >> N >> Q;
    segt[version] = new Node(0);
    segt[version]->init(0, N-1);
    int v;
    rep(i, 0, N) {
        cin >> v;
        segt[version] = segt[version]->update(i, v, 0, N-1);
    }
    currVersion[0] = 0;
    K = 1;
    int t, a, b, c;
    rep(i, 0, Q) {
        cin >> t >> a;
        a--;
        if (t == 1) {
            // Update
            cin >> b >> c;
            segt[++version] = segt[currVersion[a]]->update(b-1, c, 0, N-1);
            currVersion[a] = version;
        } else if (t == 2) {
            // Sum
            cin >> b >> c;
            cout << segt[currVersion[a]]->query(b-1, c-1, 0, N-1) << '\n';
        } else {
            // Copy
            segt[++version] = new Node(*segt[currVersion[a]]);
            currVersion[K++] = version;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}