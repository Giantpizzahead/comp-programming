#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAXN = 501, MAXP = 101;
const ll MOD = 1e9+7;
const ll RPOW = 97;

int R, C, K;
int pre[MAXN][MAXN];
char G[MAXN][MAXN];
bool works[MAXP][MAXP][MAXP];

ll power[MAXN * MAXN + 10], totalHash;

ll powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        e /= 2;
        b = b * b % m;
    }
    return r;
}

ll moddiv(ll a, ll b) {
    ll invb = powmod(b, MOD-2, MOD);
    ll r = a * invb % MOD;
    return r;
}

struct Piece {
    int r, c, topLeftI = -1, topLeftJ = -1;
    int locI, locJ;
    ll pieceHash;
    short pre[MAXP][MAXP];
    char g[MAXP][MAXP];

    void genInfo() {
        // Prefix sums & top left
        topLeftI = -1;
        topLeftJ = -1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (i == 0 && j == 0) pre[i][j] = 0;
                else if (j == 0) pre[i][j] = pre[i-1][c-1];
                else pre[i][j] = pre[i][j-1];
                if (g[i][j] != '.') {
                    pre[i][j]++;
                    if (topLeftI == -1) {
                        topLeftI = i;
                        topLeftJ = j;
                    }
                }
            }
        }

        // Hash
        pieceHash = 0;
        for (int i = 0; i < r; i++) {
            int currPow = i * C + 1;
            currPow -= topLeftI * C + topLeftJ;
            for (int j = 0; j < c; j++) {
                if (g[i][j] != '.') {
                    ll toAdd = power[currPow] * g[i][j] % MOD;
                    pieceHash = (pieceHash + toAdd) % MOD;
                }
                currPow++;
            }
        }
    }

    void genRotate(Piece& o) {
        r = o.c;
        c = o.r;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                g[i][j] = o.g[c-1-j][i];
            }
        }
        genInfo();
    }

    void genFlip(Piece& o) {
        r = o.r;
        c = o.c;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                g[i][j] = o.g[i][c-1-j];
            }
        }
        genInfo();
    }

    int queryPrefix(int x) {
        int i = x / C;
        int j = x % C;
        i -= locI;
        j -= locJ;
        if (i < 0) {
            // cout << 0 << endl;
            return 0;
        } else if (i >= r) {
            // cout << pre[r-1][c-1] << endl;
            return pre[r-1][c-1];
        }
        // Squeeze j coordinate
        if (j < 0) {
            i--;
            j = c-1;
            if (i < 0) {
                // cout << 0 << endl;
                return 0;
            }
        }
        j = min(c-1, j);
        // cout << pre[i][j] << endl;
        return pre[i][j];
    }

    // Location of the top-left filled square
    void setLocation(int i, int j) {
        locI = i - topLeftI;
        locJ = j - topLeftJ;
    }

    void print() {
        cout << "R = " << r << ", C = " << c << endl;
        cout << "TL = " << topLeftI << " " << topLeftJ << endl;
        cout << "H = " << pieceHash << endl;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << g[i][j];
            }
            cout << endl;
        }
    }
};

Piece P[MAXP][8];
unordered_map<ll, vector<int>> hashToPieces;
bool possible;

vector<Piece*> usedPieces;
pair<int, int> findTopLeft() {
    // First location where prefix != 0
    int low = 0, high = R * C;
    while (low < high) {
        int mid = (low + high) / 2;
        // cout << "pre " << mid << endl;
        int prefix = pre[mid / C][mid % C];
        for (Piece* p : usedPieces) {
            prefix -= p->queryPrefix(mid);
        }
        // cout << " = " << prefix << endl;
        if (prefix < 0) possible = false;
        if (prefix != 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return {low / C, low % C};
}

void solve() {
    cin >> K;
    cin >> R >> C;
    power[0] = 1;
    for (int i = 1; i < MAXN * MAXN + 5; i++) {
        power[i] = power[i-1] * RPOW % MOD;
    }
    string str;
    for (int i = 0; i < R; i++) {
        cin >> str;
        for (int j = 0; j < C; j++) {
            G[i][j] = str[j];
        }
    }
    // Prefix sums
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) pre[i][j] = 0;
            else if (j == 0) pre[i][j] = pre[i-1][C-1];
            else pre[i][j] = pre[i][j-1];
            if (G[i][j] != '.') {
                pre[i][j]++;
            }
        }
    }
    // Hash
    totalHash = 0;
    for (int i = 0; i < R; i++) {
        int currPow = i * C + 1;
        for (int j = 0; j < C; j++) {
            if (G[i][j] != '.') {
                ll toAdd = power[currPow] * G[i][j] % MOD;
                totalHash = (totalHash + toAdd) % MOD;
            }
            currPow++;
        }
    }
    // cout << totalHash << endl << endl;
    for (int p = 0; p < K; p++) {
        int r, c;
        cin >> r >> c;
        P[p][0].r = r;
        P[p][0].c = c;
        for (int i = 0; i < r; i++) {
            cin >> str;
            for (int j = 0; j < c; j++) {
                P[p][0].g[i][j] = str[j];
            }
        }
        P[p][0].genInfo();
        P[p][1].genRotate(P[p][0]);
        P[p][2].genRotate(P[p][1]);
        P[p][3].genRotate(P[p][2]);
        P[p][4].genFlip(P[p][0]);
        P[p][5].genRotate(P[p][4]);
        P[p][6].genRotate(P[p][5]);
        P[p][7].genRotate(P[p][6]);
        for (int i = 0; i < 8; i++) {
            if (hashToPieces.find(P[p][i].pieceHash) == hashToPieces.end()) {
                hashToPieces.emplace(P[p][i].pieceHash, vector<int>());
            }
            hashToPieces.find(P[p][i].pieceHash)->second.push_back(p);
        }
    }

    // for (int p = 0; p < K; p++) {
    //     for (int i = 0; i < 1; i++) P[p][i].print();
    //     cout << endl;
    //     cout << endl;
    //     cout << endl;
    // }

    // For every 1st piece & rotation
    pair<int, int> loc1, loc2, loc3;
    unordered_map<ll, vector<int>>::iterator ptr;
    for (int i1 = 0; i1 < K; i1++) {
        for (int r1 = 0; r1 < 8; r1++) {
            Piece& a = P[i1][r1];
            // Fix top-left position
            loc1 = findTopLeft();
            a.setLocation(loc1.first, loc1.second);
            usedPieces.push_back(&a);
            // cout << "a " << i1 << " " << r1 << endl;
            // cout << "atopleft " << loc1.first << " " << loc1.second << endl;
            
            // For every 2nd piece & rotation
            possible = true;
            loc2 = findTopLeft();
            if (!possible || loc2.first == R) {
                usedPieces.pop_back();
                continue;
            }
            for (int i2 = 0; i2 < K; i2++) {
                for (int r2 = 0; r2 < 8; r2++) {
                    if (i1 == i2) continue;
                    Piece& b = P[i2][r2];
                    // Fix top-left position
                    b.setLocation(loc2.first, loc2.second);
                    usedPieces.push_back(&b);
                    // cout << "b " << i2 << " " << r2 << endl;
                    // cout << "btopleft " << loc2.first << " " << loc2.second << endl;

                    // Fix top-left position of 3rd piece
                    possible = true;
                    loc3 = findTopLeft();
                    if (!possible || loc3.first == R) {
                        usedPieces.pop_back();
                        continue;
                    }
                    // cout << "ctopleft " << loc3.first << " " << loc3.second << endl;

                    // Calculate target hash
                    ll targetHash = totalHash;
                    targetHash -= a.pieceHash * power[loc1.first * C + loc1.second] % MOD;
                    targetHash -= b.pieceHash * power[loc2.first * C + loc2.second] % MOD;
                    // Offset for piece C
                    targetHash = (targetHash % MOD + MOD) % MOD;
                    targetHash = moddiv(targetHash, power[loc3.first * C + loc3.second]);

                    // cout << "targetHash = " << targetHash << endl;

                    ptr = hashToPieces.find(targetHash);
                    if (ptr == hashToPieces.end()) {} // cout << "no hashes" << endl;
                    else {
                        // cout << "hashes ";
                        for (int i3 : ptr->second) {
                            // cout << p->id << " ";
                            works[i1][i2][i3] = true;
                        }
                        // cout << endl;
                    }
                    usedPieces.pop_back();
                }
            }
            usedPieces.pop_back();
        }
    }

    int answer = 0;
    for (int i = 0; i < K; i++) {
        for (int j = i+1; j < K; j++) {
            for (int k = j+1; k < K; k++) {
                if (works[i][j][k] || works[j][i][k] || works[i][k][j] || works[j][k][i] || works[k][i][j] || works[k][j][i]) {
                    answer++;
                    // cout << "works " << i << " " << j << " " << k << endl;
                }
            }
        }
    }
    cout << answer << endl;
}

int main() {
    freopen("bcs.in", "r", stdin);
    freopen("bcs.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}