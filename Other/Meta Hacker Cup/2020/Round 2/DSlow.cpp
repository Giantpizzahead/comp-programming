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

vector<pair<int, int>> children[MAXN], shipments[MAXN];

int N, M;
ll P[MAXN], L[MAXN], H[MAXN], X[MAXN], Y[MAXN], answers[MAXN], tempAnswers[MAXN];

struct Query {
    int careless;
    ll startD, currAnswer;
    vector<int> currIs;
};

void dfs(int n, ll d, vector<Query> currQueries) {
    // Add queries
    for (pair<int, int>& q : shipments[n]) {
        Query newQuery;
        newQuery.careless = q.second;
        newQuery.startD = d;
        newQuery.currAnswer = 0;
        newQuery.currIs.push_back(q.first);
        currQueries.emplace_back(newQuery);
    }
    // Update queries if there is a better driver here
    for (Query& q : currQueries) {
        if (q.careless > H[n]) {
            // Update query
            q.currAnswer += q.careless * (d - q.startD);
            q.careless = H[n];
            q.startD = d;
        }
    }
    // Continue DFS
    for (pair<int, int>& e : children[n]) {
        dfs(e.first, d + e.second, currQueries);
    }
    if (children[n].empty()) {
        // Leaf node; update all answers
        for (Query& q : currQueries) {
            q.currAnswer += q.careless * (d - q.startD);
            answers[q.currIs[0]] = min(q.currAnswer, answers[q.currIs[0]]);
        }
    }
    /*
    // Merge queries if possible
    while (!currQueries.empty()) {
        Query& top = currQueries[currQueries.size()-1];
        if (top.careless >= )
    }
    */
}

void solve(int tn) {
    cout << "Case #" << tn << endl;
    for (int i = 0; i < N; i++) {
        children[i].clear();
        shipments[i].clear();
    }
    for (int i = 1; i < N; i++) {
        children[P[i]-1].emplace_back(i, L[i]);
    }
    for (int i = 0; i < M; i++) {
        shipments[X[i]-1].emplace_back(i, Y[i]);
        answers[i] = 1000000000000000000L;
    }
    dfs(0, 0, vector<Query>());

    __int128 answer = 1;
    for (int i = 0; i < M; i++) {
        answer = answer * (answers[i]+1) % 1000000007;
        // cout << answers[i]+1 << ' ';
    }
    // cout << endl;
    fout << "Case #" << tn << ": " << (ll) answer << endl;
}

void parseInput(int tn) {
    int K;
    ll Ap, Bp, Cp, Al, Bl, Cl, Dl, Ah, Bh, Ch, Dh, Ax, Bx, Cx, Ay, By, Cy, Dy;
    fin >> N >> M >> K;
    for (int i = 0; i < K; i++) {
        fin >> P[i];
    }
    fin >> Ap >> Bp >> Cp;
    for (int i = 0; i < K; i++) {
        fin >> L[i];
    }
    fin >> Al >> Bl >> Cl >> Dl;
    for (int i = 0; i < K; i++) {
        fin >> H[i];
    }
    fin >> Ah >> Bh >> Ch >> Dh;
    for (int i = 0; i < K; i++) {
        fin >> X[i];
    }
    fin >> Ax >> Bx >> Cx;
    for (int i = 0; i < K; i++) {
        fin >> Y[i];
    }
    fin >> Ay >> By >> Cy >> Dy;
    for (int i = K; i < N; i++) {
        P[i] = ((Ap * P[i-2] + Bp * P[i-1] + Cp) % i) + 1;
        L[i] = ((Al * L[i-2] + Bl * L[i-1] + Cl) % Dl) + 1;
        H[i] = ((Ah * H[i-2] + Bh * H[i-1] + Ch) % Dh) + 1;
    }
    for (int i = K; i < M; i++) {
        X[i] = ((Ax * X[i-2] + Bx * X[i-1] + Cx) % N) + 1;
        Y[i] = ((Ay * Y[i-2] + By * Y[i-1] + Cy) % Dy) + 1;
    }
    solve(tn);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}