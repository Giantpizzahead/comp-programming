/*
ID: sunnyky1
LANG: C++
TASK: shopping

Solution: DP, with lots of painful input parsing.
Runtime: O(B^5 * S)
*/

#include <iostream>
#include <fstream>
#include <algorithm>

#define MAXCODE 1000
#define MAXS 105
#define INF 987654321

using namespace std;

struct Offer {
    int N, price;
    int code[5], count[5];

    Offer() {
        // cout << "Offer made!" << endl;
    }

    ~Offer() {
        // cout << "Offer destroyed!" << endl;
    }
};

Offer offers[MAXS];
int codetoi[MAXCODE], tc[5], cc[5], pc[5];
int dp[6][6][6][6][6];

int S, B;

void eval() {
    // Try transitioning from all offers before this one
    Offer o;
    int bestTrans = INF;
    for (int i = 0; i < S; i++) {
        o = offers[i];
        // Reset previous state
        for (int i = 0; i < 5; i++) pc[i] = cc[i];
        // Calculate previous state
        for (int j = 0; j < o.N; j++) {
            if (codetoi[o.code[j]] == -1) continue;
            pc[codetoi[o.code[j]]] -= o.count[j];
        }
        // Make sure state is valid
        bool valid = true;
        for (int i = 0; i < 5; i++) {
            if (pc[i] < 0) {
                valid = false;
                break;
            }
        }
        if (valid) bestTrans = min(dp[pc[0]][pc[1]][pc[2]][pc[3]][pc[4]] + o.price, bestTrans);
    }
    dp[cc[0]][cc[1]][cc[2]][cc[3]][cc[4]] = bestTrans;
}

void genStates(int i, bool nonzero) {
    if (i == B) {
        if (nonzero) eval();
        return;
    }
    for (int a = 0; a <= tc[i]; a++) {
        cc[i] = a;
        genStates(i+1, nonzero || (a != 0));
    }
}

int main() {
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    for (int i = 0; i < MAXCODE; i++) codetoi[i] = -1;

    fin >> S;
    int N, C, K, P;
    for (int i = 0; i < S; i++) {
        fin >> N;
        offers[i].N = N;
        for (int j = 0; j < N; j++) {
            fin >> C >> K;
            offers[i].code[j] = C;
            offers[i].count[j] = K;
        }
        fin >> offers[i].price;
    }

    fin >> B;
    for (int i = 0; i < B; i++) {
        fin >> C >> K >> P;
        tc[i] = K;
        codetoi[C] = i;
        offers[S].N = 1;
        offers[S].code[0] = C;
        offers[S].count[0] = 1;
        offers[S++].price = P;
    }
    for (int i = B; i < 5; i++) tc[i] = 0;
    for (int i = 0; i < 5; i++) cc[i] = 0;

    // 5-dimensional DP! Oh my.
    dp[0][0][0][0][0] = 0;
    genStates(0, false);
    
    fout << dp[tc[0]][tc[1]][tc[2]][tc[3]][tc[4]] << endl;
    return 0;
}