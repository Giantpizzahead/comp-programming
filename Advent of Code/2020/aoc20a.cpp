#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const int M = 10;

struct Piece {
    int id, o = 0;
    bool used = false;
    bool G[M][M];

    void flip() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M/2; j++) {
                swap(G[i][j], G[i][M-1-j]);
            }
        }
    }

    void rotate90() {
        bool temp[M][M];
        swap(G, temp);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                G[j][M-1-i] = temp[i][j];
            }
        }
    }

    void nextOrientation() {
        if (o % 4 == 3) flip();
        rotate90();
        o = (o+1) % 8;
    }

    void print() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) cout << (G[i][j] ? '#' : '.');
            cout << endl;
        }
    }
};

int N = 0, D = 0;
vector<Piece> P;
vector<vector<int>> answer;
vector<bool> A(M), B(M);

void solve(int ci, int cj) {
    if (ci == D) {
        // This works
        cout << "rec " << ci << " " << cj << endl;
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < D; j++) {
                cout << P[answer[i][j]].id << ' ';
            }
            cout << endl;
        }
        long long ans = (long long) P[answer[0][0]].id * P[answer[D-1][0]].id * P[answer[0][D-1]].id * P[answer[D-1][D-1]].id;
        cout << "Answer: " << ans << endl;
        exit(0);
    }

    // Add a new piece
    for (int k = 0; k < N; k++) {
        if (P[k].used) continue;
        for (int d = 0; d < 8; d++) {
            bool valid = true;
            if (ci != 0) {
                // Border match with top
                for (int j = 0; j < M; j++) {
                    A[j] = P[k].G[0][j];
                    B[j] = P[answer[ci-1][cj]].G[M-1][j];
                }
                if (A != B) valid = false;
            }
            if (cj != 0) {
                // Border match with left
                for (int i = 0; i < M; i++) {
                    A[i] = P[k].G[i][0];
                    B[i] = P[answer[ci][cj-1]].G[i][M-1];
                }
                if (A != B) valid = false;
            }
            if (valid) {
                P[k].used = true;
                answer[ci][cj] = k;
                if (cj == D-1) solve(ci+1, 0);
                else solve(ci, cj+1);
                P[k].used = false;
            }
            P[k].nextOrientation();
        }
    }
}

void solve() {
    string s;
    while (!cin.eof()) {
        getline(cin, s);
        s = s.substr(5, 4);
        Piece p;
        p.id = stoi(s);
        for (int i = 0; i < M; i++) {
            getline(cin, s);
            for (int j = 0; j < M; j++) {
                p.G[i][j] = (s[j] == '#');
            }
        }
        P.push_back(p);
        getline(cin, s);
    }
    N = P.size();
    D = round(sqrt(N));
    cout << "N = " << N << ", D = " << D << ", M = " << M << endl;

    answer.resize(D);
    for (int i = 0; i < D; i++) answer[i].resize(D);
    // Assemble the puzzle
    solve(0, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    solve();
    fclose(stdin);
}