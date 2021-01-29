#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 105;

int N, M;
int answers[MAXN];
struct Exam {
    int s, d, c, id;
};
vector<Exam> exams;
int hasExam[MAXN];
set<pair<int, int>> active;

void solve() {
    cin >> N >> M;
    exams.resize(M);
    rep(i, 0, M) {
        cin >> exams[i].s >> exams[i].d >> exams[i].c;
        exams[i].id = i+1;
        exams[i].s--;
        exams[i].d--;
        hasExam[exams[i].d] = 1;
    }
    sort(all(exams), [](const Exam& a, const Exam& b) {
        return a.s < b.s;
    });
    int i = 0;
    rep(d, 0, N) {
        while (i != M && exams[i].s == d) {
            active.emplace(exams[i].d, i);
            i++;
        }
        // Greedily prepare for earliest test date first
        if (hasExam[d] == 1) {
            // Not ready
            cout << -1 << '\n';
            return;
        } else if (hasExam[d] == 2) {
            // Ready
            answers[d] = M+1;
            continue;
        }
        // Prepare
        if (active.empty()) {
            answers[d] = 0;
            continue;
        }
        int toPrep = active.begin()->second;
        answers[d] = exams[toPrep].id;
        exams[toPrep].c--;
        if (exams[toPrep].c == 0) {
            hasExam[exams[toPrep].d] = 2;
            active.erase(active.begin());
        }
    }

    rep(i, 0, N) {
        if (i != 0) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}