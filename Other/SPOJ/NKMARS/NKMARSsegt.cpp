#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

// #define DEBUG cout
#ifndef DEBUG
    #define DEBUG if (false) cout
#endif

const int MAXC = 30005;
const int MAXC_SEG = MAXC * 4 + 1;

struct Event {
    int x, a, b;
    bool s;
    Event(int x, int a, int b, int s) : x(x), a(a), b(b), s(s) {}
};

struct SegmentTree {
    // vals[n] = # ranges that completely cover node n
    int vals[MAXC_SEG], delta[MAXC_SEG], nonzero[MAXC_SEG];

    SegmentTree() {
        for (int i = 0; i < MAXC_SEG; i++) {
            vals[i] = 0;
            delta[i] = 0;
            nonzero[i] = 0;
        }
    }

    void propagate(int n, int lb, int ub) {
        vals[n*2] += delta[n];
        vals[n*2+1] += delta[n];
        delta[n*2] += delta[n];
        delta[n*2+1] += delta[n];
        delta[n] = 0;
    }

    void merge(int n, int lb, int ub) {
        if (vals[n] == 0) nonzero[n] = nonzero[n*2] + nonzero[n*2+1];
        else nonzero[n] = ub - lb + 1;
    }

    void increment(int l, int r, int n = 1, int lb = 0, int ub = MAXC - 1) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            vals[n]++;
            nonzero[n] = ub - lb + 1;
            delta[n]++;
            return;
        }

        propagate(n, lb, ub);
        increment(l, r, n*2, lb, (lb+ub)/2);
        increment(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n, lb, ub);
    }

    void decrement(int l, int r, int n = 1, int lb = 0, int ub = MAXC - 1) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r && vals[n] != 1) {
            // Still covered; no need to go down
            vals[n]--;
            delta[n]--;
            return;
        } else if (lb == ub) {
            // Base case
            vals[n] = 0;
            delta[n] = 0;
            nonzero[n] = 0;
            return;
        }

        if (lb >= l && ub <= r) vals[n]--;
        propagate(n, lb, ub);
        decrement(l, r, n*2, lb, (lb+ub)/2);
        decrement(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n, lb, ub);
    }

    int query() {
        DEBUG << "query " << nonzero[1] << endl;
        // for (int i = 0; i < MAXC_SEG; i++) DEBUG << vals[i] << ' ';
        // DEBUG << endl;
        return nonzero[1];
    }
};

int N;
SegmentTree segt;
vector<Event> events;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    events.reserve(N * 2);
    int x1, y1, x2, y2;
    for (int i = 0; i < N; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        events.emplace_back(x1, y1, y2, true);
        events.emplace_back(x2, y1, y2, false);
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x;
    });

    ll answer = 0;
    int lastX = 0, i = 0;
    while (i < events.size()) {
        int currX = events[i].x;

        // Update area
        DEBUG << currX << " " << answer << endl;
        answer += (currX - lastX) * segt.query();

        while (i < events.size() && events[i].x == currX) {
            Event& e = events[i];
            if (e.s) {
                segt.increment(e.a, e.b - 1);
            } else {
                segt.decrement(e.a, e.b - 1);
            }
            i++;
        }
        lastX = currX;
    }

    cout << answer << endl;
}