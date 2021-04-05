#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
vi cards;
vi ans, other;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

void solve() {
    srand(time(NULL));
    cin >> N;
    rep(i, 0, 6*N) cards.push_back(i+1);
    bool turn = true;
    while (!cards.empty()) {
        int s = randint(0, sz(cards)-3);
        if (turn) {
            ans.push_back(cards[s]);
            ans.push_back(cards[s+1]);
            ans.push_back(cards[s+2]);
        } else {
            other.push_back(cards[s]);
            other.push_back(cards[s+1]);
            other.push_back(cards[s+2]);
        }
        cards.erase(cards.begin()+s);
        cards.erase(cards.begin()+s);
        cards.erase(cards.begin()+s);
        turn = !turn;
    }
    for (int x : ans) cout << x << ' ';
    cout << endl;
    for (int x : other) cout << x << ' ';
    cout << endl;
    sort(all(ans));
    for (int x : ans) cout << x << ' ';
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}