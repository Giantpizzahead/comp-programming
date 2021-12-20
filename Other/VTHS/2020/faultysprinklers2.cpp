#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double A, B, C, D;

struct Line {
    double m, b;

    double intersectX(Line& o) {
        return (o.b - b) / (m - o.m);
    }

    double eval(double x) {
        return m * x + b;
    }

    void print() {
        cout << "(" << m << ",  " << b << ")" << endl;
    }
};

struct Hull {
    vector<Line> lines;

    // Assumes monotonic slope
    void insert(Line& l) {
        if (!lines.empty() && abs(lines[lines.size()-1].m - l.m) < 1e-9) {
            // By sorting, this one is better
            lines.pop_back();
        }
        while (lines.size() > 1) {
            if (lines[lines.size()-2].intersectX(lines[lines.size()-1]) >= lines[lines.size()-1].intersectX(l)) {
                // Invariant violated
                lines.pop_back();
            } else break;
        }
        lines.push_back(l);
    }

    double query(double x, bool isMin) {
        double res = isMin ? 1e18 : -1e18;
        for (Line& l : lines) {
            if (isMin) res = min(l.eval(x), res);
            else res = max(l.eval(x), res);
        }
        return res;
    }

    void print() {
        cout << "{" << endl;
        for (Line& l : lines) l.print();
        cout << "}" << endl;
    }
};

struct Point {
    double x, y;

    void print() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

Line la, lb, lc, ld;
int N;
Point P[4];
vector<Line> tempLines;
vector<double> events;
Hull botHull, topHull;

void solve() {
    cin >> A >> B >> C >> D;
    // if (A == 0) A = 1e-15;
    // if (B == 0) B = 1e-15;
    // if (C == 0) C = 1e-15;
    // if (D == 0) D = 1e-15;
    if (A == 90 || B == 90 || C == 90 || D == 90) {
        cout << 1.0 << endl;
        return;
    }
    A *= M_PI / 180;
    B *= M_PI / 180;
    C *= M_PI / 180;
    D *= M_PI / 180;
    la = {-1/tan(A), 1/tan(A)};
    lb = {tan(B), 1-tan(B)};
    lc = {-1/tan(C), 1};
    ld = {tan(D), 0};
    // cout << "lines:\n";
    // la.print();
    // lb.print();
    // lc.print();
    // ld.print();

    if (C != 0) tempLines.push_back(lc);
    if (D != 0) tempLines.push_back(ld);
    tempLines.push_back({0, 0});
    sort(tempLines.begin(), tempLines.end(), [](const Line& a, const Line& b) {
        if (a.m == b.m) return a.b < b.b;
        else return a.m < b.m;
    });
    for (Line& l : tempLines) botHull.insert(l);
    tempLines.clear();

    if (A != 0) tempLines.push_back(la);
    if (B != 0) tempLines.push_back(lb);
    tempLines.push_back({0, 1});
    sort(tempLines.begin(), tempLines.end(), [](const Line& a, const Line& b) {
        if (a.m == b.m) return a.b > b.b;
        else return a.m > b.m;
    });
    for (Line& l : tempLines) topHull.insert(l);
    tempLines.clear();

    // botHull.print();
    // topHull.print();

    // Find area using hull (find all intersection points)
    events.push_back(0);
    events.push_back(1);
    for (Line& a : topHull.lines) {
        for (Line& b : botHull.lines) {
            double intersect = a.intersectX(b);
            if (intersect > 0 && intersect < 1) events.push_back(intersect);
        }
    }
    for (int i = 1; i < topHull.lines.size(); i++) {
        double intersect = topHull.lines[i].intersectX(topHull.lines[i-1]);
        if (intersect > 0 && intersect < 1) events.push_back(intersect);
    }
    for (int i = 1; i < botHull.lines.size(); i++) {
        double intersect = botHull.lines[i].intersectX(botHull.lines[i-1]);
        if (intersect > 0 && intersect < 1) events.push_back(intersect);
    }
    sort(events.begin(), events.end());
    // for (double x : events) cout << x << endl;

    // Sweep to determine area
    double lastX = 0, totalArea = 0;
    for (double x : events) {
        if (abs(lastX - x) < 1e-9) {
            lastX = x;
            continue;  // Duplicate event
        }
        // Is area positive?
        double bot1 = botHull.query(lastX, false);
        double top1 = topHull.query(lastX, true);
        double bot2 = botHull.query(x, false);
        double top2 = topHull.query(x, true);
        // cout << x << ": " << bot2 << " " << top2 << endl;
        double height = ((top1-bot1) + (top2-bot2)) / 2;
        double area = (x-lastX) * height;
        if (area > 0) totalArea += area;
        lastX = x;
    }
    cout << 1 - totalArea << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    cout << fixed << setprecision(9);
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}