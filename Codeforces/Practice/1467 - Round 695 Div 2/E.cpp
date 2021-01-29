#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, cl = 0, answer;
unordered_map<int, int> cnt, minLabelS, maxLabelE;
int A[MAXN], labelS[MAXN], labelE[MAXN];
bool hasPathST[MAXN], hasPathAbove[MAXN];
vi adj[MAXN];

void dfsLabel(int n, int p) {
    labelS[n] = cl++;
    if (minLabelS.find(A[n]) == minLabelS.end()) minLabelS[A[n]] = 1e9;
    minLabelS[A[n]] = min(labelS[n], minLabelS[A[n]]);
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsLabel(e, n);
    }
    labelE[n] = cl - 1;
    maxLabelE[A[n]] = max(labelE[n], maxLabelE[A[n]]);
}

multiset<int> above;
set<int>* dfsPaths(int n, int p) {
    if (n != p) hasPathAbove[n] = hasPathAbove[p];
    if (minLabelS[A[n]] < labelS[n] || maxLabelE[A[n]] > labelE[n]) hasPathAbove[n] = true;
    above.insert(A[n]);

    vector<set<int>*> nums;
    int exclusive = -1;
    for (int e : adj[n]) {
        if (e == p) continue;
        set<int>* s = dfsPaths(e, n);
        nums.push_back(s);
        hasPathST[n] |= hasPathST[e];
        if (s->count(A[n]) != 0) {
            if (exclusive == -1) exclusive = e;
            else hasPathAbove[n] = true;
        }
    }
    // Update hasPathST
    if (exclusive != -1) {
        for (int e : adj[n]) {
            if (e == p || e == exclusive) continue;
            hasPathAbove[e] = true;
        }
    }
    if (nums.empty()) {
        set<int>* s = new set<int>();
        s->insert(A[n]);
        return s;
    }
    // Merge
    while (nums.size() > 1) {
        if (nums[sz(nums)-1]->size() > nums[sz(nums)-2]->size()) swap(nums[sz(nums)-1], nums[sz(nums)-2]);
        for (int x : *nums[sz(nums)-1]) nums[sz(nums)-2]->insert(x);
        delete nums[sz(nums)-1];
        nums.pop_back();
    }
    if (nums[0]->count(A[n]) != 0) hasPathST[n] = true;
    nums[0]->insert(A[n]);

    above.erase(above.find(A[n]));
    return nums[0];
}

void dfsRoots(int n, int p) {
    if (n != p) hasPathAbove[n] |= hasPathAbove[p];
    if (!hasPathST[n] && !hasPathAbove[n]) answer++;
    int inST = -1;
    for (int e : adj[n]) {
        if (e == p) continue;
        if (hasPathST[e]) {
            if (inST != -1) return;  // Two STs with duplicates
            inST = e;
        }
    }
    for (int e : adj[n]) {
        if (e == p || (inST != -1 && e != inST)) continue;
        dfsRoots(e, n);
    }
}

void solve() {
    cin >> N;
    cnt.reserve(N);
    minLabelS.reserve(N);
    maxLabelE.reserve(N);
    rep(i, 0, N) {
        cin >> A[i];
        cnt[A[i]]++;
    }
    rep(i, 1, N) {
        int a, b;
        cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsLabel(0, 0);
    delete dfsPaths(0, 0);
    dfsRoots(0, 0);
    // rep(i, 0, N) cout << hasPathST[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << hasPathAbove[i] << ' ';
    // cout << endl;
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}