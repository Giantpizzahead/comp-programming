#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 300000;
const int MAXS = 500000;

int N;
pair<int, int> bn[MAXN];
string str;

int query(int x, int y) {
    int result = 0;
    for (pair<int, int>& p : bn) {
        if ((p.first < x) == (p.second < y)) {
            // Max
            result = max(max(abs(p.first - x), abs(p.second - y)), result);
        } else {
            // Sum
            result = max(abs(p.first - x) + abs(p.second - y), result);
        }
    }
    return result;
}

void printAnswer(int minQueryVal, int bestB, int bestN) {
    cout << minQueryVal << endl;
    while (bestB > 0 || bestN > 0) {
        if (bestB != 0 && bestN != 0) {
            cout << "BN";
            bestB--;
            bestN--;
        } else if (bestB != 0) {
            cout << 'B';
            bestB--;
        } else if (bestN != 0) {
            cout << 'N';
            bestN--;
        }
    }
    cout << endl;
}

void doSearch(int x1, int y1, int x2, int y2) {
    // cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;

    if ((ll) (x2 - x1) * (y2 - y1) < 300) {
        // Just brute force at this point
        int minQueryVal = 987654321, minX = -1, minY = -1;
        for (int i = x1; i <= x2; i++) {
            for (int j = x1; j <= x2; j++) {
                if (i == 0 && j == 0) continue;
                int queryRes = query(i, j);
                if (queryRes < minQueryVal) {
                    minQueryVal = queryRes;
                    minX = i;
                    minY = j;
                }
            }
        }
        printAnswer(minQueryVal, minX, minY);
        return;
    }

    int xmid = (x1 + x2) / 2;
    int ymid = (y1 + y2) / 2;

    int queries[3][3];
    int minQueryVal = 987654321;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            queries[i][j] = query(xmid-1+i, ymid+1-j);
            minQueryVal = min(queries[i][j], minQueryVal);
        }
    }
    
    if (queries[1][1] == minQueryVal) {
        // Found best loc; print it
        printAnswer(minQueryVal, xmid, ymid);
        return;
    } else if (queries[0][0] == minQueryVal) {
        doSearch(x1, ymid+1, xmid-1, y2);
    } else if (queries[2][0] == minQueryVal) {
        doSearch(xmid+1, ymid+1, x2, y2);
    } else if (queries[0][2] == minQueryVal) {
        doSearch(x1, y1, xmid-1, ymid-1);
    } else if (queries[2][2] == minQueryVal) {
        doSearch(xmid+1, y1, x2, ymid-1);
    } else if (queries[0][1] == minQueryVal) {
        doSearch(x1, y1, xmid-1, ymid);
    } else if (queries[2][1] == minQueryVal) {
        doSearch(xmid+1, y1, x2, y2);
    } else if (queries[1][0] == minQueryVal) {
        doSearch(x1, ymid+1, x2, y2);
    } else if (queries[1][2] == minQueryVal) {
        doSearch(x1, y1, x2, ymid-1);
    }
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> str;
        int numN = 0, numB = 0;
        for (int j = 0; j < str.size(); j++) {
            if (str[j] == 'N') numN++;
            else numB++;
        }
        bn[i].first = numB;
        bn[i].second = numN;
    }
    
    // Ternary search...?
    doSearch(0, 0, MAXS, MAXS);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}