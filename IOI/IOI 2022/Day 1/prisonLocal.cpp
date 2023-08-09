/*
IOI 2022 Day 1: Prison
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N, nextX;
map<int, int> pairToNum;
vector<vector<int>> S;

int getPairID(int a, int b) {
    return a*3 + b;
}

void genNum(int depth, int category) {
    // if (getPairID(depth, category) == 21) return;
    if (pairToNum.find(getPairID(depth, category)) == pairToNum.end()) {
        vector<int> currRow = vector<int>(N+1, -3);
        S.push_back(currRow);
        pairToNum[getPairID(depth, category)] = nextX++;
    }
}

int dfs(int depth, int category, int l, int r, int pl, int pr) {
    // if (getPairID(depth, category) == 21) return -1;
    int num = pairToNum[getPairID(depth, category)];
    // cout << "num = " << num << endl;
    // cout << num << ": dfs(" << depth << ", " << category << ", " << l << ", " << r << ")" << endl;

    // Can immediately stop if coins inspected are <=l or >=r
    bool onBagB = (depth % 2);
    S[num][0] = onBagB;
    rep(i, pl, l+1) S[num][i] = (onBagB ? -2 : -1);
    rep(i, r, pr+1) S[num][i] = (onBagB ? -1 : -2);
    l++, r--;
    int currN = r-l+1;

    // Do a ternary search split if N is greater than 2
    if (currN <= 0) return num;

    if (depth < 6) {
        int l1 = l;
        int r1 = l + currN/3 - 1;
        int l2 = r1+1;
        int r2 = l + (currN*2)/3 - 1;
        int l3 = r2+1;
        int r3 = r;

        rep(i, 0, 3) genNum(depth+1, i);
        int num1 = dfs(depth+1, 0, l1, r1, l-1, r+1);
        int num2 = dfs(depth+1, 1, l2, r2, l-1, r+1);
        int num3 = dfs(depth+1, 2, l3, r3, l-1, r+1);

        rep(i, l1, r1+1) S[num][i] = num1;
        rep(i, l2, r2+1) S[num][i] = num2;
        rep(i, l3, r3+1) S[num][i] = num3;
    } else {
        // Binary search
        cout << "binary " << currN << endl;
        int l1 = l;
        int r1 = l + currN/2 - 1;
        int l2 = r1+1;
        int r2 = r;

        rep(i, 0, 2) genNum(depth+1, i);
        int num1 = dfs(depth+1, 0, l1, r1, l-1, r+1);
        int num2 = dfs(depth+1, 1, l2, r2, l-1, r+1);
        
        rep(i, l1, r1+1) S[num][i] = num1;
        rep(i, l2, r2+1) S[num][i] = num2;
    }

    return num;
}

vector<vector<int>> devise_strategy(int n) {
    N = n;
    S.clear();
    nextX = 0;
    pairToNum.clear();
    genNum(0, 0);
    dfs(0, 0, 1, N, 1, N);
    for (auto& p : pairToNum) cout << p.first << " " << p.second << endl;
    return S;
}

int main() {
    int N = 5000;
    devise_strategy(N);
    int x = ((int) S.size()) - 1;
    cout << "N = " << N << ", x = " << x << endl;
    rep(i, 0, x+1) {
        cout << i << ": ";
        map<char, int> cnt;
        rep(j, 0, N+1) {
            int x = S[i][j];
            string s = to_string(x);
            if (x == -1) s = "A";
            if (x == -2) s = "B";
            if (x == -3) s = " ";
            // cout << s << " ";
            cnt[s[0]]++;
        }
        for (auto p : cnt) cout << p.first << " " << p.second << ", ";
        cout << endl;
    }

    // Try this strategy
    int currNum = 0;
    int A = 14;
    int B = 15;
    while (true) {
        cout << "On " << currNum << ", ";
        int i = (S[currNum][0] == 0 ? A : B);
        if (S[currNum][i] == -1) {
            cout << "A has fewer" << endl;
            break;
        } else if (S[currNum][i] == -2) {
            cout << "B has fewer" << endl;
            break;
        } else {
            cout << "Going to " << S[currNum][i] << endl;
            currNum = S[currNum][i];
        }
    }
    return 0;
}
