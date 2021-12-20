#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int N;
ll answer;
vector<int> A;
vector<int> mqInc, mqDec;

struct SegmentTree {
    vector<int> V;
    vector<bool> zeroDelta;

    void init() {
        V.resize(N*4+1);
        zeroDelta.resize(N*4+1);
    }

    void propagate(int n) {
        if (zeroDelta[n]) {
            zeroDelta[n*2] = true;
            zeroDelta[n*2+1] = true;
            V[n*2] = 0;
            V[n*2+1] = 0;
            zeroDelta[n] = false;
        }
    }

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void zero(int l, int r, int n = 1, int lb = 1, int ub = N) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            zeroDelta[n] = true;
            V[n] = 0;
            return;
        }
        propagate(n);
        zero(l, r, n*2, lb, (lb+ub)/2);
        zero(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void increment(int i, int v, int n = 1, int lb = 1, int ub = N) {
        if (lb == ub) {
            V[n] += v;
            return;
        }
        propagate(n);
        if (i > (lb+ub)/2) increment(i, v, n*2+1, (lb+ub)/2+1, ub);
        else increment(i, v, n*2, lb, (lb+ub)/2);
        merge(n);
    }

    int query(int l, int r, int n = 1, int lb = 1, int ub = N) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        propagate(n);
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
};

SegmentTree segt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    A.resize(N);
    segt.init();
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    for (int i = 0; i < N; i++) {
        // Maintain monotonic queues
        while (!mqInc.empty() && A[i] < A[*mqInc.rbegin()]) {
            // Remove this from segment tree
            int toRemove = *mqInc.rbegin();
            int m = *lower_bound(mqDec.begin(), mqDec.end(), toRemove);
            segt.increment(A[m], -1);
            mqInc.pop_back();
        }
        mqInc.push_back(i);
        while (!mqDec.empty() && A[i] > A[*mqDec.rbegin()]) {
            mqDec.pop_back();
        }
        mqDec.push_back(i);

        // cout << "mqInc: ";
        // for (int x : mqInc) cout << x << ' ';
        // cout << endl;
        // cout << "mqDec: ";
        // for (int x : mqDec) cout << x << ' ';
        // cout << endl;
        // cout << endl;

        // Add this to segment tree & move all elements with smaller
        int toMove = segt.query(1, A[i]-1);
        segt.zero(1, A[i]-1);
        segt.increment(A[i], toMove + 1);

        // Update answer
        answer += segt.query(1, A[i]);
    }
    cout << answer << endl;
    return 0;
}