#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const int MAXN = 100001;
const int GROUP_SIZE = 316;

int N, K, Q;
int H[MAXN], bitL[MAXN], bitI[MAXN], bitR[MAXN];

struct Query {
    int l, r, id;

    bool operator<(const Query& o) const {
        // Different blocks?
        int b = l / GROUP_SIZE;
        int bo = o.l / GROUP_SIZE;
        if (b != bo) return b < bo;
        else return r < o.r;
    }
};

struct BIT {
    int V[MAXN];

    BIT() {
        for (int i = 0; i < MAXN; i++) V[i] = 0;
    }

    void update(int i, int v) {
        i++;
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query0(int i) {
        i++;
        int R = 0;
        while (i > 0) {
            R += V[i];
            i -= i & -i;
        }
        return R;
    }

    int query(int l, int r) {
        return query0(r) - query0(l-1);
    }
};

Query queries[MAXN];
ll answers[MAXN];
BIT bit;
ll currPairs = 0;

void bitAdd(int i) {
    // cout << "add " << i << endl;
    currPairs += bit.query(bitL[i], bitR[i]);
    bit.update(bitI[i], 1);
}

void bitRemove(int i) {
    // cout << "remove " << i << endl;
    bit.update(bitI[i], -1);
    currPairs -= bit.query(bitL[i], bitR[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> H[i];
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }
    sort(queries, queries+Q);

    // Coordinate compression
    vector<pair<int, int>> comp;
    for (int i = 0; i < N; i++) {
        comp.emplace_back(H[i], i);
    }
    sort(comp.begin(), comp.end());

    int li = 0, ri = 0;
    for (int i = 0; i < N; i++) {
        while (ri != N-1 && comp[ri+1].first <= comp[i].first + K) ri++;
        while (comp[li].first < comp[i].first - K) li++;
        bitL[comp[i].second] = li;
        bitI[comp[i].second] = i;
        bitR[comp[i].second] = ri;
        // cout << li << " " << i << " " << ri << " -> " << comp[i].second << endl;
    }

    li = 0;
    ri = -1;
    for (int i = 0; i < Q; i++) {
        Query& q = queries[i];
        // Move to correct location
        while (ri < q.r) bitAdd(++ri);
        while (ri > q.r) bitRemove(ri--);
        while (li > q.l) bitAdd(--li);
        while (li < q.l) bitRemove(li++);
        // cout << q.l << " " << q.r << endl;
        answers[q.id] = currPairs;
    }

    for (int i = 0; i < Q; i++) cout << answers[i] << '\n';
    return 0;
}