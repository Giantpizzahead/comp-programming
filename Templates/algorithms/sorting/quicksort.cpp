#include <ctime>
#include <random>

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