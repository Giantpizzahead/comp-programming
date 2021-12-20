#include <algorithm>

void bubbleSort(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = N-1; j > i; j--) {
            if (arr[j] < arr[j-1]) std::swap(arr[j], arr[j-1]);
        }
    }
}