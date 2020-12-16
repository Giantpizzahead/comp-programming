#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ld = long double;

const int MAXN = 2e5+5;

struct Spell {
    int a, b, id;
};

struct Line {
    ld m, b;
    int id;
    ld eval(int x) {
        return m * x + b;
    }
    ld intersect(Line& o) {
        return (o.b - b) / (m - o.m);
    }
};

int N, M;
Spell spells[MAXN];
pair<int, int> monsters[MAXN];
int answers[MAXN];
vector<Line> lines;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> spells[i].a >> spells[i].b;
        spells[i].id = i+1;
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> monsters[i].first;
        monsters[i].second = i;
    }
    sort(monsters, monsters+M);
    sort(spells, spells+N, [](const Spell& a, const Spell& b) {
        return (a.b - a.a) > (b.b - b.a);
    });

    for (int i = 0; i < N; i++) {
        if (spells[i].a == spells[i].b) continue;
        ld slope = -1.0 / (spells[i].b - spells[i].a);
        Line line = {slope, -slope * spells[i].a, spells[i].id};
        bool shouldAdd = true;
        while (!lines.empty()) {
            // Check same slopes
            Line& topLine = lines[lines.size()-1];
            if (abs(line.m - topLine.m) <= 1e-20) {
                // Equal slopes; which is better?
                if (line.b > topLine.b) {
                    // This one
                    lines.pop_back();
                } else {
                    // Other one
                    shouldAdd = false;
                    break;
                }
            } else break;
        }
        if (!shouldAdd) continue;
        // Invariant
        while (lines.size() >= 2) {
            if (lines[lines.size()-2].intersect(lines[lines.size()-1]) < lines[lines.size()-1].intersect(line)) {
                lines.pop_back();
            } else break;
        }
        // cout << "adding " << spells[i].id << endl;
        lines.push_back(line);
    }

    sort(spells, spells+N, [](const Spell& a, const Spell& b) {
        return a.a < b.a;
    });
    for (int i = 0; i < M; i++) {
        int x = monsters[i].first;
        if (x <= spells[N-1].a) {
            answers[monsters[i].second] = spells[N-1].id;
            continue;
        }
        // Remove bad lines
        while (lines.size() >= 2) {
            if (lines[lines.size()-1].eval(x) <= lines[lines.size()-2].eval(x)) {
                // Takeover!
                lines.pop_back();
            } else break;
        }
        if (!lines.empty()) answers[monsters[i].second] = lines[lines.size()-1].id;
        else answers[monsters[i].second] = 1;
    }

    for (int i = 0; i < M; i++) {
        if (i != 0) cout << ' ';
        cout << answers[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}