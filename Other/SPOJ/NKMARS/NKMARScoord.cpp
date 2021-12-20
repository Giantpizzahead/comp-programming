#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXC = 30001;

struct Event {
    int x, a, b;
    bool s;
    Event(int x, int a, int b, int s) : x(x), a(a), b(b), s(s) {}
};

int N;
int active[MAXC];
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
        for (int j = 0; j < MAXC; j++) {
            if (active[j] != 0) answer += currX - lastX;
        }

        while (i < events.size() && events[i].x == currX) {
            Event& e = events[i];
            if (e.s) {
                for (int j = e.a; j < e.b; j++) active[j]++;
            } else {
                for (int j = e.a; j < e.b; j++) active[j]--;
            }
            i++;
        }
        lastX = currX;
    }

    cout << answer << endl;
}