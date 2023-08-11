/*
When can a cow catch an apple?
(x_c, t_c) and (x_a, t_a)
Only when t_a >= t_c and abs(x_a - x_c) <= t_a - t_c.

Plot x on the x axis, t on the y axis. Then each cow can catch apples in a V shape above it.
Rotate 45 degrees: y axis is (t - x), x axis is (t + x). Now each cow's shape is an L.

This can then be solved by a greedy sweepline algorithm. Sort by x-axis, adding cows when you come
across, and greedily using up the highest y coordinate cows that can be paired with the current apples.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

struct Point {
    bool isApple;
    int x, y, n, id;
};

const int INF = 1e9;

int N;
vector<Point> P;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        int q, t, x, n; cin >> q >> t >> x >> n;
        int nx = t + x, ny = t - x;
        P.push_back({(q == 2), nx, ny, n, i});
        // cout << "new: " << nx << " " << ny << endl;
    }

    sort(all(P), [](const Point& a, const Point& b){
        // Order by increasing x, putting cows before apples in case of a tie
        return make_pair(a.x, a.isApple) < make_pair(b.x, b.isApple);
    });

    // Sweep
    struct Cow {
        int y, n, id;
        bool operator<(const Cow& o) const {
            // Order by increasing y, breaking ties by unique id
            return make_pair(y, id) < make_pair(o.y, o.id);
        }
    };
    set<Cow> cows;
    int answer = 0;
    for (Point& p : P) {
        if (p.isApple) {
            // Use cows greedily
            while (p.n > 0 && !cows.empty()) {
                auto ptr = cows.upper_bound({p.y, -1, INF});
                if (ptr == cows.begin()) break;
                ptr = prev(ptr);
                // cout << "using " << ptr->y << " " << ptr->n << " " << ptr->id << endl;
                // Use this
                if (ptr->n <= p.n) {
                    answer += ptr->n;
                    p.n -= ptr->n;
                    cows.erase(ptr);
                } else {
                    answer += p.n;
                    Cow newCow = {ptr->y, ptr->n - p.n, ptr->id};
                    cows.erase(ptr);
                    cows.insert(newCow);
                    p.n = 0;
                }
                // cout << "answer = " << answer << endl;
            }
        } else {
            cows.insert({p.y, p.n, p.id});
        }
    }
    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
