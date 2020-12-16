/**
 * Main takeaway: Although the radix sort method of constructing a suffix array is much quicker than the std sort
 * method, it won't matter much in competitive programming contests (both take <1 second for N, Q = 5 * 10^5). The
 * difference matters once N exceeds 5 * 10^5.
 * 
 * Despite the seemingly large overhead, the radix sort generation method does work pretty well for very large values of
 * N, even up to 3 million! Don't be afraid to use suffix arrays, even if N is really large.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
using namespace std;

#define printArray(s, e)\
cout << "[";\
for (auto x = s; x != e; x++) {\
    if (x != s) cout << ", ";\
    cout << *x;\
}\
cout << "]" << endl

const int MAXN = 3e6;
const int LOGN = 23;

int N, Q;
bool checkAnswer;
int queryA[MAXN], queryB[MAXN];
int answerS[MAXN], answerQ[MAXN];
string str;

struct BaseSuffixArray {
    string str;
    int S[MAXN];

    virtual void init(string& str) {
        this->str = str;
    }

    virtual int lcp(int a, int b) = 0;

    void print() {
        printArray(S, S+N);
    }

    void printVerbose() {
        for (int i = 0; i < N; i++) {
            for (int j = S[i]; j < N; j++) cout << str[j];
            cout << endl;
        }
    }
};

/**
 * Sorts suffixes in a naive way.
 * Init: O(N^2 * log(N))
 * Queries LCP by simply going through the two suffixes, character by character.
 * LCP query: O(N)
 */
struct SuffixArrayN2logN : public BaseSuffixArray {
    string suffixes[MAXN];
    void init(string& str) {
        BaseSuffixArray::init(str);

        // Generate all suffixes & sort them
        for (int i = 0; i < N; i++) {
            suffixes[i] = str.substr(i);
        }
        sort(suffixes, suffixes+N);
        for (int i = 0; i < N; i++) {
            S[i] = N - suffixes[i].length();
        }
    }

    int lcp(int a, int b) {
        for (int l = 0; l < min(suffixes[a].length(), suffixes[b].length()); l++) {
            if (suffixes[a][l] != suffixes[b][l]) return l;
        }
        return min(suffixes[a].length(), suffixes[b].length());
    }
};

/**
 * Sorts the first 2^k characters in each iteration.
 * Uses std sort to sort the pairs that represent each suffix.
 * Init: O(N * log^2(N))
 * Queries LCP using binary-search on the loc array.
 * LCP query: O(log(N))
 */
struct SuffixArrayNlog2N : public BaseSuffixArray {
    int loc[LOGN][MAXN];
    pair<pair<int, int>, int> toSort[MAXN];

    void init(string& str) {
        BaseSuffixArray::init(str);

        // Sort first character
        for (int i = 0; i < N; i++) {
            toSort[i].first.first = str[i];
            toSort[i].first.second = -1;
            toSort[i].second = i;
        }
        sort(toSort, toSort+N);
        int classes = 0, last1 = -2, last2 = -2;
        for (int i = 0; i < N; i++) {
            if (last1 != toSort[i].first.first || last2 != toSort[i].first.second) {
                last1 = toSort[i].first.first;
                last2 = toSort[i].first.second;
                classes++;
            }
            loc[0][toSort[i].second] = classes;
        }
        
        // Sort by first 2^k characters
        for (int k = 1; k <= ceil(log2(N)); k++) {
            for (int i = 0; i < N; i++) {
                toSort[i].first.first = loc[k-1][i];
                int ni = i + (1 << k-1);
                if (ni >= N) ni = -1;
                else ni = loc[k-1][ni];
                toSort[i].first.second = ni;
                toSort[i].second = i;
            }
            sort(toSort, toSort+N);
            classes = 0, last1 = -2, last2 = -2;
            for (int i = 0; i < N; i++) {
                if (last1 != toSort[i].first.first || last2 != toSort[i].first.second) {
                    last1 = toSort[i].first.first;
                    last2 = toSort[i].first.second;
                    classes++;
                }
                loc[k][toSort[i].second] = classes;
            }
        }
        // for (int k = 0; k <= ceil(log2(N)); k++) {
        //     for (int i = 0; i < N; i++) cout << loc[k][i] << ' ';
        //     cout << endl;
        // }

        // Generate the suffix array
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

/**
 * Sorts the first 2^k characters per iteration.
 * Uses radix sort when sorting the pairs representing the suffixes.
 * Init: O(N * log(N))
 * To top it all off, uses a sparse table for LCP queries in constant time.
 * LCP query: O(1)
 */
struct SuffixArrayNlogN : public BaseSuffixArray {
    int loc[LOGN][MAXN], lcpArr[MAXN], sparseLCP[LOGN][MAXN];
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
        BaseSuffixArray::init(str);

        // Sort first character
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

        // Sort first 2^k characters
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

        // Generate suffix array
        for (int i = 0; i < N; i++) {
            toSort[i].first = loc[static_cast<int>(ceil(log2(N)))][N-1-i];
            toSort[i].second = N-1-i;
        }
        countingSort(N);
        for (int i = 0; i < N; i++) S[i] = toSort[i].second;

        // Generate LCP array
        for (int i = 0; i < N-1; i++) {
            int a = S[i], b = S[i+1], l = 0;
            for (int k = ceil(log2(N)); k >= 0; k--) {
                if (loc[k][a] == loc[k][b]) {
                    a += 1 << k;
                    a %= N;
                    b += 1 << k;
                    b %= N;
                    l += 1 << k;
                }
            }
            lcpArr[i] = l;
        }
        lcpArr[N-1] = INT32_MAX;

        // Create sparse table from LCP array
        for (int i = 0; i < N; i++) sparseLCP[0][i] = lcpArr[i];
        for (int k = 1; k <= ceil(log2(N)); k++) {
            for (int i = 0; i < N; i++) {
                sparseLCP[k][i] = sparseLCP[k-1][i];
                int ni = i + (1 << k-1);
                if (ni < N) sparseLCP[k][i] = min(sparseLCP[k-1][ni], sparseLCP[k][i]);
                // cout << sparseLCP[k][i] << " ";
            }
            // cout << endl;
        }
    }

    int lcp(int a, int b) {
        if (a == b) return N - S[a];
        b--;
        // 0 -> 0, 1/2 -> 1, 3/4/5/6 -> 2
        int k = floor(log2(b-a+1));
        return min(sparseLCP[k][a], sparseLCP[k][b+1-(1<<k)]);
    }
};

SuffixArrayN2logN sa1;
SuffixArrayNlog2N sa2;
SuffixArrayNlogN sa3;

void testSuffixArray(BaseSuffixArray& sa, string name, int maxN = INT32_MAX) {
    name += ':';
    while (name.length() < 12) name += ' ';
    cout << name << ' ';
    if (N > maxN) {
        cout << "X" << endl;
        return;
    }
    auto start = chrono::system_clock::now();
    sa.init(str);
    if (N <= 100) sa.print();
    if (N <= 10) sa.printVerbose();
    bool correctAnswer = true;
    if (checkAnswer) {
        for (int i = 0; i < N; i++) {
            if (sa.S[i] != answerS[i]) {
                correctAnswer = false;
                break;
            }
        }
    }
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end - start;
    start = chrono::system_clock::now();
    for (int i = 0; i < Q; i++) {
        int result = sa.lcp(queryA[i], queryB[i]);
        if (checkAnswer && result != answerQ[i]) correctAnswer = false;
        if (Q <= 10) cout << "lcp(" << queryA[i] << ", " << queryB[i] << ") = " << result << endl;
    }
    if (!correctAnswer) {
        cout << "---WRONG---" << endl;
        return;
    }
    end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end - start;
    cout << fixed << elapsed_seconds1.count() << "s, " << elapsed_seconds2.count() << "s" << endl;
}

int main() {
    // cin >> N >> Q;
    N = 500000;
    Q = 500000;
    srand(chrono::system_clock::now().time_since_epoch().count());
    N--;
    for (int i = 0; i < N; i++) {
        int x = rand() % (N + 26);
        if (x >= 26) str += 'o';
        else str += x % 26 + 'a';
    }
    str += '#';
    N = str.length();
    for (int i = 0; i < Q; i++) {
        while (true) {
            int a = rand() % N;
            int b = rand() % N;
            if (a == b) continue;
            else if (a > b) swap(a, b);
            if (b - a > sqrt(N)+1) continue;
            // if (b - a > log2(N)+1) continue;
            queryA[i] = a;
            queryB[i] = b;
            break;
        }
    }
    cout << "N = " << N << ", Q = " << Q << endl;
    if (N <= 100) cout << "str = " << str << endl;

    testSuffixArray(sa1, "naive", 50000);
    if (N <= 50000) {
        // Check answer
        checkAnswer = true;
        for (int i = 0; i < N; i++) answerS[i] = sa1.S[i];
        for (int i = 0; i < Q; i++) answerQ[i] = sa1.lcp(queryA[i], queryB[i]);
    }
    testSuffixArray(sa2, "std sort", 500000);
    testSuffixArray(sa3, "radix sort", 3000000);
    return 0;
}