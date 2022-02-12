#include "fun.h"

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

vector<int> createFunTour(int N, int Q) {
    int H = hoursRequired(0, N - 1);
    int A = attractionsBehind(0, N - 1);
    return vector<int>(N);
}
