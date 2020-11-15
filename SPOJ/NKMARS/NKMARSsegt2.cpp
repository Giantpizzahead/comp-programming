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
    int minVal[MAXC_SEG], minCount[MAXC_SEG], delta[MAXC_SEG];

    SegmentTree() {
        initSeg(1, 0, MAXC - 1);
    }

    void initSeg(int n, int lb, int ub) {
        if (lb == ub) {
            minVal[n] = 0;
            minCount[n] = 1;
            delta[n] = 0;
        } else {
            initSeg(n*2, lb, (lb+ub)/2);
            initSeg(n*2+1, (lb+ub)/2+1, ub);
            minVal[n] = 0;
            minCount[n] = ub-lb+1;
            delta[n] = 0;
        }
    }

    void propagate(int n) {
        minVal[n*2] += delta[n];
        minVal[n*2+1] += delta[n];
        delta[n*2] += delta[n];
        delta[n*2+1] += delta[n];
        delta[n] = 0;
    }

    void merge(int n) {
        minVal[n] = min(minVal[n*2], minVal[n*2+1]);
        minCount[n] = 0;
        if (minVal[n*2] == minVal[n]) minCount[n] += minCount[n*2];
        if (minVal[n*2+1] == minVal[n]) minCount[n] += minCount[n*2+1];
    }

    void update(int l, int r, int x, int n = 1, int lb = 0, int ub = MAXC - 1) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            minVal[n] += x;
            delta[n] += x;
            return;
        }

        propagate(n);
        update(l, r, x, n*2, lb, (lb+ub)/2);
        update(l, r, x, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    int query() {
        int answer = MAXC;
        if (minVal[1] == 0) answer -= minCount[1];
        DEBUG << "query " << answer << endl;
        // for (int i = 0; i < MAXC_SEG; i++) DEBUG << vals[i] << ' ';
        // DEBUG << endl;
        return answer;
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
                segt.update(e.a, e.b - 1, 1);
            } else {
                segt.update(e.a, e.b - 1, -1);
            }
            i++;
        }
        lastX = currX;
    }

    cout << answer << endl;
}