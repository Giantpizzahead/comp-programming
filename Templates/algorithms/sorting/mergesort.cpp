#include <vector>

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