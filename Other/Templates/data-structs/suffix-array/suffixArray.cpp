#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 3e6 + 5;
const int LOGN = 23;
int N = 100;

struct SuffixArray {
    int S[MAXN], loc[LOGN][MAXN];
    pair<int, int> toSort[MAXN], tempSort[MAXN];

    int cnt[MAXN];
    void countingSort(int A) {
        for (int i = 0; i <= A; i++) cnt[i] = 0;
        for (int i = 0; i < N; i++) cnt[toSort[i].first]++;
        for (int i = 1; i <= A; i++) cnt[i] += cnt[i-1];
        for (int i = N-1; i >= 0; i--) tempSort[--cnt[toSort[i].first]] = toSort[i];
        for (int i = 0; i < N; i++) toSort[i] = tempSort[i];
    }

    void init(string& str) {
        for (int i = 0; i < N; i++) {
            toSort[i].first = str[i];
            toSort[i].second = i;
        }
        countingSort(256);
        int classes = 0, last1 = -2, last2 = -2;
        for (int i = 0; i < N; i++) {
            if (toSort[i].first != last1) {
                last1 = toSort[i].first;
                classes++;
            }
            loc[0][toSort[i].second] = classes;
        }
        for (int k = 1; k <= ceil(log2(N)); k++) {
            for (int i = 0; i < N; i++) {
                int ni = toSort[i].second - (1 << k-1);
                if (ni < 0) ni += N;
                toSort[i].first = loc[k-1][ni];
                toSort[i].second = ni;
            }
            countingSort(N);
            classes = 0, last1 = -2, last2 = -2;
            for (int i = 0; i < N; i++) {
                int ni = toSort[i].second + (1 << k-1);
                if (ni >= N) ni -= N;
                if (toSort[i].first != last1 || loc[k-1][ni] != last2) {
                    last1 = toSort[i].first;
                    last2 = loc[k-1][ni];
                    classes++;
                }
                loc[k][toSort[i].second] = classes;
            }
        }
        for (int i = 0; i < N; i++) {
            toSort[i].first = loc[static_cast<int>(ceil(log2(N)))][N-1-i];
            toSort[i].second = N-1-i;
        }
        countingSort(N);
        for (int i = 0; i < N; i++) S[i] = toSort[i].second;
    }

    int lcp(int a, int b) {
        a = S[a];
        b = S[b];
        int l = 0;
        for (int k = ceil(log2(N)); k >= 0; k--) {
            if (loc[k][a] == loc[k][b]) {
                a += 1 << k;
                a %= N;
                b += 1 << k;
                b %= N;
                l += 1 << k;
            }
        }
        return l;
    }
};