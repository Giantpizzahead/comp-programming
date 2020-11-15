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