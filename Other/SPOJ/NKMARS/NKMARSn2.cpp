#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 10005;

struct Event {
    int x, a, b;
    bool s;
    Event(int x, int a, int b, int s) : x(x), a(a), b(b), s(s) {}
};

int N;
multiset<pair<int, bool>> active;
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
        // cout << currX << " " << answer << endl;
        int lastY = 0, numActive = 0;
        for (auto p : active) {
            if (numActive != 0) answer += (currX - lastX) * (p.first - lastY);
            if (p.second) {
                numActive++;
            } else {
                numActive--;
            }
            lastY = p.first;
        }

        while (i < events.size() && events[i].x == currX) {
            Event& e = events[i];
            if (e.s) {
                active.emplace(e.a, true);
                active.emplace(e.b, false);
            } else {
                active.erase(active.find({e.a, true}));
                active.erase(active.find({e.b, false}));
            }
            i++;
        }
        lastX = currX;
    }

    cout << answer << endl;
}