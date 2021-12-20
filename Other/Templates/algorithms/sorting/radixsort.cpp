// Good choices for B:
// (int) sqrt(max in arr) + 1
// max(N, 2)

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