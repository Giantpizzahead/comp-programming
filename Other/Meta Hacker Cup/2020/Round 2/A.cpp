#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 1000005;

int N;
ll S[MAXN], X[MAXN], Y[MAXN];
vector<int> lessThan, moreThan, ok;

void output(ll answer, int tn) {
    /*
    for (int i = 0; i < N; i++) {
        cout << S[i] << ' ';
    }
    cout << endl;
    */
    fout << "Case #" << tn << ": " << answer << endl;
}

void solve(int tn) {
    // cout << "Case " << tn << endl;
    int K;
    ll As, Bs, Cs, Ds, Ax, Bx, Cx, Dx, Ay, By, Cy, Dy;
    fin >> N >> K;

    for (int i = 0; i < K; i++) {
        fin >> S[i];
    }
    fin >> As >> Bs >> Cs >> Ds;
    for (int i = 0; i < K; i++) {
        fin >> X[i];
    }
    fin >> Ax >> Bx >> Cx >> Dx;
    for (int i = 0; i < K; i++) {
        fin >> Y[i];
    }
    fin >> Ay >> By >> Cy >> Dy;
    
    for (int i = K; i < N; i++) {
        S[i] = ((As * S[i-2] + Bs * S[i-1] + Cs) % Ds);
        X[i] = ((Ax * X[i-2] + Bx * X[i-1] + Cx) % Dx);
        Y[i] = ((Ay * Y[i-2] + By * Y[i-1] + Cy) % Dy);
    }

    // Greedily move customers from too much to too little & vice versa first
    lessThan.clear();
    moreThan.clear();
    ok.clear();
    ll answer = 0;

    for (int i = 0; i < N; i++) {
        if (S[i] > X[i] + Y[i]) {
            // Too many
            moreThan.push_back(i);
        } else if (S[i] < X[i]) {
            // Too little
            lessThan.push_back(i);
        } else {
            ok.push_back(i);
        }
    }

    // cout << "mt\n";
    while (!moreThan.empty()) {
        int i = moreThan[moreThan.size()-1];
        int needToMove = S[i] - (X[i] + Y[i]);
        // cout << needToMove << endl;
        while (!lessThan.empty() && needToMove > 0) {
            int top = lessThan[lessThan.size()-1];
            int canTake = X[top] - S[top];
            if (needToMove >= canTake) {
                // Must keep searching
                answer += canTake;
                S[top] += canTake;
                S[i] -= canTake;
                needToMove -= canTake;
                lessThan.pop_back();
                ok.push_back(top);
            } else {
                // Done
                answer += needToMove;
                S[top] += needToMove;
                S[i] -= needToMove;
                needToMove = 0;
                break;
            }
        }
        if (needToMove > 0) break;
        else {
            moreThan.pop_back();
            ok.push_back(i);
        }
    }

    // cout << "lt\n";
    while (!lessThan.empty()) {
        int i = lessThan[lessThan.size()-1];
        int needToTake = X[i] - S[i];
        // cout << needToTake << endl;
        while (!moreThan.empty() && needToTake > 0) {
            int top = moreThan[moreThan.size()-1];
            int canMove = S[top] - (X[top] + Y[top]);
            if (needToTake >= canMove) {
                // Must keep searching
                answer += canMove;
                S[top] -= canMove;
                S[i] += canMove;
                needToTake -= canMove;
                moreThan.pop_back();
                ok.push_back(top);
            } else {
                // Done
                answer += needToTake;
                S[top] -= needToTake;
                S[i] += needToTake;
                needToTake = 0;
                break;
            }
        }
        if (needToTake > 0) break;
        else {
            lessThan.pop_back();
            ok.push_back(i);
        }
    }

    if (!lessThan.empty() && !moreThan.empty()) {
        cout << "NOT BOTH EMPTY!" << endl;
    }

    // cout << "mt2\n";
    if (!moreThan.empty()) {
        // Take from ones that are already satisfied
        while (!moreThan.empty()) {
            int i = moreThan[moreThan.size()-1];
            int needToMove = S[i] - (X[i] + Y[i]);
            // cout << needToMove << endl;
            while (!ok.empty() && needToMove > 0) {
                int top = ok[ok.size()-1];
                int canTake = (X[top] + Y[top]) - S[top];
                if (needToMove >= canTake) {
                    // Must keep searching
                    answer += canTake;
                    S[top] += canTake;
                    S[i] -= canTake;
                    needToMove -= canTake;
                    ok.pop_back();
                } else {
                    // Done
                    answer += needToMove;
                    S[top] += needToMove;
                    S[i] -= needToMove;
                    needToMove = 0;
                    break;
                }
            }
            if (needToMove > 0) {
                // Impossible
                output(-1, tn);
                return;
            } else moreThan.pop_back();
        }
    }

    // cout << "lt2\n";
    if (!lessThan.empty()) {
        // Take from ones that are already satisfied
        while (!lessThan.empty()) {
            int i = lessThan[lessThan.size()-1];
            int needToTake = X[i] - S[i];
            // cout << needToTake << endl;
            while (!ok.empty() && needToTake > 0) {
                int top = ok[ok.size()-1];
                int canMove = S[top] - X[top];
                if (needToTake >= canMove) {
                    // Must keep searching
                    answer += canMove;
                    S[top] -= canMove;
                    S[i] += canMove;
                    needToTake -= canMove;
                    ok.pop_back();
                } else {
                    // Done
                    answer += needToTake;
                    S[top] -= needToTake;
                    S[i] += needToTake;
                    needToTake = 0;
                    break;
                }
            }
            if (needToTake > 0) {
                // Impossible
                output(-1, tn);
                return;
            } else lessThan.pop_back();
        }
    }

    // If got here, not impossible; output answer
    output(answer, tn);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}
