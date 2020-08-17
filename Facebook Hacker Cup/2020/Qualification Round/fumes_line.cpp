#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

typedef long long ll;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define MAXN 1000000
#define SEGT_SIZE 2100000
#define INF 4223372036854775807L

namespace segt {
    ll arr[SEGT_SIZE * 4 + 1];

    void init() {
        for (int i = 0; i < SEGT_SIZE * 4 + 1; i++) {
            arr[i] = INF;
        }
    }

    void update(int n, int lb, int ub, int i, ll v) {
        if (lb > i || ub < i) return;
        else if (lb == ub) {
            arr[n] = min(v, arr[n]);
            return;
        }
        update(n*2, lb, (lb+ub)/2, i, v);
        update(n*2+1, (lb+ub)/2+1, ub, i, v);
        arr[n] = min(arr[n*2], arr[n*2+1]);
    }

    void update(int i, ll v) {
        update(1, 0, SEGT_SIZE - 1, i, v);
    }

    ll query(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return INF;
        else if (lb >= l && ub <= r) return arr[n];
        return min(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, SEGT_SIZE - 1, l, r);
    }
}

int N, M, A, B;
ll cost[MAXN];
bool is_on_path[MAXN];
vector<int> adj[MAXN];
vector<int> on_path;
unordered_map<int, ll> refuel_costs[MAXN];

stack<int> node_stack;
void find_on_path(int n, int p) {
    node_stack.push(n);
    if (n == B) {
        // Found end node; currently have the right stack
        while (!node_stack.empty()) {
            int t = node_stack.top();
            node_stack.pop();
            is_on_path[t] = true;
            on_path.push_back(t);
        }
        return;
    }

    for (int e : adj[n]) {
        if (e != p) find_on_path(e, n);
        if (node_stack.empty()) return;  // Found end node already
    }
    node_stack.pop();
}

void fill_refueling_costs(int n, int p, int d, int initial_n) {
    if (cost[n] != 0) {
        // Add possible refueling cost
        auto prev = refuel_costs[initial_n].find(d);
        if (prev == refuel_costs[initial_n].end()) {
            refuel_costs[initial_n][d] = cost[n];
        } else {
            refuel_costs[initial_n][d] = min(cost[n], refuel_costs[initial_n][d]);
        }
    }
    for (int e : adj[n]) {
        if (e != p && !is_on_path[e]) fill_refueling_costs(e, n, d+1, initial_n);
    }
}

void solve(int tn) {
    // cout << "-----------" << endl;
    fin >> N >> M;
    A = 0;
    B = N - 1;
    int p, c;
    for (int i = 0; i < N; i++) {
        p = i - 1;
        fin >> c;
        if (p != -1) {
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        cost[i] = c;
    }

    // Find all nodes on path from A to B
    find_on_path(A, A);

    // Now, fill in refueling costs for all nodes on the path
    for (int i = 0; i < N; i++) {
        if (is_on_path[i]) fill_refueling_costs(i, i, 0, i);
    }

    // for (int n : on_path) {
    //     cout << n+1 << ':' << endl;
    //     for (auto const& p : refuel_costs[n]) {
    //         cout << p.first << ' ' << p.second << endl;
    //     }
    // }

    // Finally, simulate going through the path, using a segment tree to update minimum
    // cost efficiently
    int zero_loc = 0, refuel_dist, refuel_cost;
    segt::init();
    segt::update(zero_loc + M, 0);
    for (int n : on_path) {
        for (auto const& p : refuel_costs[n]) {
            refuel_dist = p.first;
            refuel_cost = p.second;
            // Try using this refuel
            ll best_cost = segt::query(zero_loc + refuel_dist, zero_loc + M);
            segt::update(zero_loc + M - refuel_dist, best_cost + refuel_cost);
        }
        // Moving to a new node = Used up one more gallon
        zero_loc++;
    }
    zero_loc--;

    // Must have non-negative amount of fuel left
    ll answer = segt::query(zero_loc, zero_loc + M);
    if (answer >= INF) {
        // Impossible
        answer = -1;
    }
    fout << "Case #" << tn << ": " << answer << endl;

    // Reset stuff
    for (int i = 0; i < N; i++) {
        adj[i].clear();
        is_on_path[i] = false;
        refuel_costs[i].clear();
    }
    on_path.clear();
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}
