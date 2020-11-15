#include <algorithm>

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