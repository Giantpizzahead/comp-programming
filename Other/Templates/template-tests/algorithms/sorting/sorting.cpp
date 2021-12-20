#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <chrono>
#include <functional>
#include <iomanip>
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

void timeSort(string sortName, function<void(int*, int)> func) {
    cout << sortName << "\t";
    genArr();
    auto startTime = getTime();
    func(arr, N);
    chrono::duration<double> elapsed = getTime() - startTime;
    cout << fixed << elapsed.count() << " seconds" << endl;
    compareArrs(sortedArr, arr, N);
    if (N <= 20) printArr(arr, N);
}

// BEGIN TEMPLATES

void bubbleSort(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = N-1; j > i; j--) {
            if (arr[j] < arr[j-1]) std::swap(arr[j], arr[j-1]);
        }
    }
}

void countingSort(int* arr, int N) {
    int C = arr[0];
    for (int i = 1; i < N; i++) if (arr[i] > C) C = arr[i];
    int cnt[C+1], newArr[N];
    for (int i = 0; i <= C; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) cnt[arr[i]]++;
    for (int i = 1; i <= C; i++) cnt[i] += cnt[i-1];
    for (int i = N-1; i >= 0; i--) newArr[--cnt[arr[i]]] = arr[i];
    for (int i = 0; i < N; i++) arr[i] = newArr[i];
}

std::vector<int>* mergeSortRec(int* arr, int l, int r) {
    std::vector<int>* result = new std::vector<int>();
    result->reserve(r-l+1);
    if (l == r) result->push_back(arr[l]);
    else {
        std::vector<int>& left = *mergeSortRec(arr, l, (l+r)/2);
        std::vector<int>& right = *mergeSortRec(arr, (l+r)/2+1, r);
        int li = 0, ri = 0;
        for (int i = 0; i < r-l+1; i++) {
            if (ri == right.size() || (li != left.size() && left[li] < right[ri])) result->push_back(left[li++]);
            else result->push_back(right[ri++]);
        }
        // Free memory
        delete &left;
        delete &right;
    }
    return result;
}

void mergeSort(int* arr, int N) {
    std::vector<int>& result = *mergeSortRec(arr, 0, N-1);
    for (int i = 0; i < N; i++) arr[i] = result[i];
    delete &result;
}

void quickSortRec(int* arr, int l, int r) {
    if (l >= r) return;
    int p = arr[rand() % (r-l+1) + l];
    int pl = l, pr = r;
    for (int i = l; i <= pr; i++) {
        if (arr[i] < p) std::swap(arr[i], arr[pl++]);
        else if (arr[i] > p) std::swap(arr[i--], arr[pr--]);
    }
    quickSortRec(arr, l, pl-1);
    quickSortRec(arr, pr+1, r);
}

void quickSort(int* arr, int N) {
    srand(time(NULL));
    quickSortRec(arr, 0, N-1);
}

void radixCountingSort(int* arr, int* A, int N, int B) {
    int cnt[B], newArr[N];
    for (int i = 0; i < B; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) cnt[A[i]]++;
    for (int i = 1; i < B; i++) cnt[i] += cnt[i-1];
    for (int i = N-1; i >= 0; i--) newArr[--cnt[A[i]]] = arr[i];
    for (int i = 0; i < N; i++) arr[i] = newArr[i];
}

void radixSort(int* arr, int N, int B) {
    long long C = arr[0];
    for (int i = 1; i < N; i++) if (arr[i] > C) C = arr[i];
    int A[N];
    long long x = B;
    do {
        for (int i = 0; i < N; i++) {
            A[i] = arr[i] / (x / B);
            A[i] %= B;
        }
        radixCountingSort(arr, A, N, B);
        x *= B;
    } while (x <= C * B);
}

void radixSort10(int* arr, int N) {
    radixSort(arr, N, 10);
}

void radixSortSqrtC(int* arr, int N) {
    int C = arr[0];
    for (int i = 1; i < N; i++) if (arr[i] > C) C = arr[i];
    radixSort(arr, N, (int) sqrt(C) + 1);
}

void radixSortN(int* arr, int N) {
    radixSort(arr, N, max(N, 2));
}

void shellSort(int* arr, int N) {
    int gap = N/2;
    while (gap != 0) {
        for (int i = gap; i < N; i++) {
            for (int j = i; j >= gap && arr[j-gap] > arr[j]; j -= gap) {
                std::swap(arr[j-gap], arr[j]);
            }
        }
        gap /= 2;
    }
}

// END TEMPLATES

int main() {
    N = 15000;
    C = 100000;

    cout << "N = " << N << ", C = " << C << endl;

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        origArr[i] = genRand(1, C);
        sortedArr[i] = origArr[i];
    }
    sort(sortedArr, sortedArr+N);

    if (N <= 20) printArr(origArr, N);
    timeSort("Quick sort   ", quickSort);
    timeSort("Shell sort   ", shellSort);
    timeSort("Merge sort   ", mergeSort);
    timeSort("Bubble sort  ", bubbleSort);
    timeSort("Counting sort", countingSort);
    timeSort("Radix sqrt(C)", radixSortSqrtC);
    timeSort("Radix N      ", radixSortN);
    timeSort("Radix 10     ", radixSort10);
    return 0;
}