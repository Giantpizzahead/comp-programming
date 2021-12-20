/**
Takeaways:

Counting sort and radix sort are actually quite a lot faster than standard sorting algorithms if you're just sorting
numbers. In addition, both of these sorts are pretty easy to implement!

For radix sort, the best base to use is sqrt(C) in most cases, giving a complexity of O(2[N + sqrt(C)]).

The choice is really between standard sort, counting sort, and radix sort (the other sorts don't have any advantages).

Empirical data (No optimization when compiling, Sorts are left out if they aren't interesting):

N = 1000000, C = 1000000 (Random)
Counting sort   0.021701 seconds
Radix sqrt(C)   0.059797 seconds
Radix N         0.072649 seconds
Standard sort   0.176954 seconds
Radix 10        0.207202 seconds
Quick sort      0.282128 seconds
Shell sort      0.529239 seconds
Merge sort      0.752026 seconds
Bubble sort     X

N = 10000000, C = 10000000 (Random)
Counting sort   0.348164 seconds
Radix sqrt(C)   0.629703 seconds
Radix N         1.057355 seconds
Standard sort   2.110364 seconds
Radix 10        2.412411 seconds
Quick sort      X
Shell sort      X
Merge sort      X

N = 50000000, C = 50000000 (Random)
Counting sort   1.804306 seconds
Radix sqrt(C)   3.177086 seconds
Radix N         5.132690 seconds
Standard sort   11.450418 seconds
Radix 10        12.027416 seconds

N = 100000, C = 1000000000 (Random)
Radix sqrt(C)   0.006452 seconds
Radix N         0.007085 seconds
Standard sort   0.014965 seconds
Quick sort      0.024649 seconds
Radix 10        0.029729 seconds
Shell sort      0.037644 seconds
Merge sort      0.070926 seconds
Counting sort   X

N = 50000000, C = 100000 (Random)
Counting sort   0.476035 seconds
Radix N         1.905701 seconds
Radix sqrt(C)   2.998787 seconds
Radix 10        8.965922 seconds
Standard sort   9.946417 seconds

N = 1000000, C = 1000000 (Increasing)
Shell sort      0.034907 seconds
Standard sort   0.066545 seconds
Quick sort      0.239623 seconds

N = 1000000, C = 1000000 (Decreasing)
Standard sort   0.059348 seconds
Shell sort      0.111958 seconds
Quick sort      0.238720 seconds

N = 1000000, C = 1000000 (All the same)
Quick sort      0.001884 seconds
Shell sort      0.035077 seconds
Standard sort   0.118870 seconds
**/

#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <chrono>
#include <functional>
#include <iomanip>
#include <mcheck.h>
using namespace std;

const int MAXN = 1e8;

int N, C;
int origArr[MAXN], sortedArr[MAXN], arr[MAXN];

inline int genRand(int l, int r) {
    return rand() % (r-l+1) + l;
}

inline auto getTime() {
    return chrono::system_clock::now();
}

inline void printArr(int* A, int N) {
    cout << "[";
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ", ";
        cout << A[i];
    }
    cout << "]" << endl;
}

void compareArrs(int* A, int* B, int N) {
    for (int i = 0; i < N; i++) {
        if (A[i] != B[i]) {
            cout << "*** ARRAYS DIFFER!!! ***" << endl;
            break;
        }
    }
}

void genArr() {
    for (int i = 0; i < N; i++) arr[i] = origArr[i];
}

void timeSort(string sortName, function<void()> func, int maxN = INT32_MAX, int maxC = INT32_MAX) {
    cout << sortName << "\t";
    if (N > maxN || C > maxC) {
        cout << "X" << endl;
        return;
    }
    genArr();
    auto startTime = getTime();
    func();
    chrono::duration<double> elapsed = getTime() - startTime;
    cout << fixed << elapsed.count() << " seconds" << endl;
    if (N <= 1000000) compareArrs(sortedArr, arr, N);
    if (N <= 20) printArr(arr, N);
}

// BEGIN SORTING METHODS

// O(N * log(N))
void stdSort() {
    sort(arr, arr+N);
}

// O(N * log(N))
void quickSortRec(int l, int r) {
    if (l >= r) return;
    // Choose random pivot
    int p = arr[rand() % (r-l+1) + l];
    // Create partition (one with less, one with equal, one with greater)
    int pl = l, pr = r;
    for (int i = l; i <= pr; i++) {
        if (arr[i] < p) {
            // On left
            swap(arr[i], arr[pl++]);
        } else if (arr[i] > p) {
            // On right
            swap(arr[i--], arr[pr--]);
        }
    }
    // Recursively sort
    quickSortRec(l, pl-1);
    quickSortRec(pr+1, r);
}
void quickSort() {
    quickSortRec(0, N-1);
}

// O(N * log(N)) average, O(N^2) worst
void shellSort() {
    int gap = N/2;
    while (gap != 0) {
        // Do insertion sort for this gap size
        for (int i = gap; i < N; i++) {
            for (int j = i; j >= gap && arr[j-gap] > arr[j]; j -= gap) {
                swap(arr[j-gap], arr[j]);
            }
        }
        gap /= 2;
    }
}

// O(N * log(N))
vector<int>* mergeSortRec(int l, int r) {
    vector<int>* result = new vector<int>();
    result->reserve(r-l+1);
    if (l == r) {
        result->push_back(arr[l]);
    } else {
        // Divide and conquer!
        vector<int>& left = *mergeSortRec(l, (l+r)/2);
        vector<int>& right = *mergeSortRec((l+r)/2+1, r);
        int li = 0, ri = 0;
        for (int i = 0; i < r-l+1; i++) {
            if (ri == right.size() || (li != left.size() && left[li] < right[ri])) {
                // Left element first
                result->push_back(left[li++]);
            } else {
                // Right element first
                result->push_back(right[ri++]);
            }
        }
        // Free memory
        delete &left;
        delete &right;
    }
    return result;
}
void mergeSort() {
    vector<int>& result = *mergeSortRec(0, N-1);
    for (int i = 0; i < N; i++) arr[i] = result[i];
    delete &result;
}

// O(N^2)
void bubbleSort() {
    for (int i = 0; i < N; i++) {
        for (int j = N-1; j > i; j--) {
            if (arr[j] < arr[j-1]) swap(arr[j], arr[j-1]);
        }
    }
}

// O(N + C)
void countingSort() {
    int cnt[C+1], newArr[N];
    // Generate cnt array (# of elements with each value)
    for (int i = 0; i <= C; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) cnt[arr[i]]++;
    // Prefix sums for cnt
    for (int i = 1; i <= C; i++) cnt[i] += cnt[i-1];
    // Find place in final array
    for (int i = N-1; i >= 0; i--) newArr[--cnt[arr[i]]] = arr[i];
    // Replace arr with newArr
    for (int i = 0; i < N; i++) arr[i] = newArr[i];
}

// O((N + B) * logB(C))
void radixCountingSort(int* A, int B) {
    // cout << "counting sort B = " << B << endl;
    int cnt[B], newArr[N];
    for (int i = 0; i < B; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) cnt[A[i]]++;
    for (int i = 1; i < B; i++) cnt[i] += cnt[i-1];
    for (int i = N-1; i >= 0; i--) newArr[--cnt[A[i]]] = arr[i];
    for (int i = 0; i < N; i++) arr[i] = newArr[i];
    // printArr(arr, N);
}
void radixSort(long long B) {
    int A[MAXN];
    long long x = B;
    do {
        // Generate radix array
        for (int i = 0; i < N; i++) {
            A[i] = arr[i] / (x / B);
            A[i] %= B;
        }
        // printArr(A, N);
        radixCountingSort(A, B);
        x *= B;
    } while (x <= C * B);
}

// O(2[N + sqrt(C)])
void radixSortSqrtC() {
    radixSort(static_cast<int>(sqrt(C)) + 1);
}

// O(2N * logN(C))
void radixSortN() {
    radixSort(max(N, 2));
}

// O(N * log10(C))
void radixSort10() {
    radixSort(10);
}

// END SORTING METHODS

int main() {
    N = 1000000;
    C = 100000000;

    cout << "N = " << N << ", C = " << C << endl;

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        origArr[i] = genRand(1, C);
        sortedArr[i] = origArr[i];
    }
    if (N <= 1000000) sort(sortedArr, sortedArr+N);

    if (N <= 20) printArr(origArr, N);
    timeSort("Standard sort", stdSort);
    timeSort("Quick sort   ", quickSort, 3000000);
    timeSort("Shell sort   ", shellSort, 1500000);
    timeSort("Merge sort   ", mergeSort, 1000000);
    timeSort("Bubble sort  ", bubbleSort, 15000);
    timeSort("Counting sort", countingSort, 100000000, 100000000);
    timeSort("Radix sqrt(C)", radixSortSqrtC);
    timeSort("Radix N      ", radixSortN);
    timeSort("Radix 10     ", radixSort10, 10000000);
    return 0;
}