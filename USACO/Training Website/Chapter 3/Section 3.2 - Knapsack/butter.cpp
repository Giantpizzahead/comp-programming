/*
ID: sunnyky1
LANG: C++
TASK: butter

Solution: For every possible location to put the sugar, run a
Dijkstra to the other pastures to find the total distance
traveled.
Runtime: O(PC * log(C))
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXP 800
#define INF 987654321

using namespace std;

struct Edge {
    int n, c;
    Edge(int n, int c) : n(n), c(c) {}

    bool operator<(const Edge& o) const {
        return c - o.c > 0;
    }
};

int N, P, C;
int cowsInPasture[MAXP];
vector<Edge> adj[MAXP];

int eval(int sn) {
    int currCost = 0;
    int bestDist[P];
    for (int i = 0; i < P; i++) bestDist[i] = INF;
    bestDist[sn] = 0;
    priority_queue<Edge> pq;
    pq.push(Edge(sn, 0));

    while (!pq.empty()) {
        Edge c = pq.top();
        pq.pop();
        if (c.c != bestDist[c.n]) continue;
        currCost += c.c * cowsInPasture[c.n];

        for (Edge e : adj[c.n]) {
            if (c.c + e.c < bestDist[e.n]) {
                bestDist[e.n] = c.c + e.c;
                pq.push(Edge(e.n, bestDist[e.n]));
            }
        }
    }

    // for (int i = 0; i < P; i++) cout << bestDist[i] << ' ';
    // cout << endl;

    return currCost;
}

int main() {
    ifstream fin("butter.in");
    ofstream fout("butter.out");

    fin >> N >> P >> C;
    for (int i = 0; i < P; i++) cowsInPasture[i] = 0;
    int a, b, c;
    for (int i = 0; i < N; i++) {
        fin >> a;
        cowsInPasture[--a]++;
    }
    for (int i = 0; i < C; i++) {
        fin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back(Edge(b, c));
        adj[b].push_back(Edge(a, c));
    }

    // Find min distance for each pasture
    int currMin = INF;
    for (int i = 0; i < P; i++) {
        currMin = min(eval(i), currMin);
        // cout << "Eval " << i << " = " << eval(i) << endl;
    }
    fout << currMin << endl;

    fin.close();
    fout.close();
}