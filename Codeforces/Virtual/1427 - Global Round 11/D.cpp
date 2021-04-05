#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 53;

int N;
int A[MAXN], temp[MAXN];

vector<string> moves;
vector<int> pieces;

void doOp() {
    if (sz(pieces) == 1) {
        pieces.clear();
        return;
    }
    string move = to_string(sz(pieces));
    for (int x : pieces) move += " " + to_string(x);
    // cout << "move " << move << endl;
    moves.push_back(move);
    int j = 1, k = N+1;
    for (int x : pieces) {
        rep(i, 0, x) {
            temp[k-x+i] = A[j+i];
        }
        k -= x;
        j += x;
    }
    swap(A, temp);
    // rep(i, 1, N+1) cout << A[i] << ' ';
    // cout << endl;
    pieces.clear();
}

void addPiece(int x) {
    if (x != 0) pieces.push_back(x);
}

void solve() {
    cin >> N;
    rep(i, 1, N+1) {
        cin >> A[i];
    }
    rep(i, 1, N+1) {
        if (N % 2 == 1 && i == N) break;
        int loc = 0;
        rep(j, 1, N+1) {
            if (A[j] == i) {
                loc = j;
                break;
            }
        }
        if (i % 2 == 1) {
            // Move number to right side
            rep(j, 1, i) addPiece(1);
            addPiece(loc+1-i);
            addPiece(N-loc);
        } else {
            // Move number to left side
            addPiece(loc-1);
            addPiece(N-loc-i+2);
            rep(j, 1, i) addPiece(1);
        }
        doOp();
    }

    cout << sz(moves) << '\n';
    for (string& s : moves) cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}