#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 1000005;

int N;
int arr[MAXN];

void solve(ll sumn) {
    /*cin >> N;
    ll sum = 0;
    ll x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        sum += x;
    }*/
    N = 6;
    for (int i = 0; i < N; i++) arr[i] = 5;
    arr[N-1] = sumn;
    
    bool happened = true;
    while (happened) {
        happened = false;
        for (int j = N-1; j > 0; j--) {
            if (arr[j-1] + 2 <= arr[j]) {
                arr[j]--;
                arr[j-1]++;
                happened = true;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << arr[i]-i;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    for (int i = 5; i < 50; i++) solve(i);
    return 0;
}