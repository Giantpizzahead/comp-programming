#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200000;
int N, K;
int arr[MAXN];
vector<int> splits;

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> arr[i];

    splits.clear();
    for (int i = 0; i < N; i++) {
        if (splits.size() == K - 1) break;
        if (arr[i] % 2 == 1) {
            // Split here
            splits.push_back(i+1);
        }
    }

    // Make sure last split works
    bool isOdd = false;
    for (int i = (splits.size() == 0 ? 0 : splits[splits.size()-1]); i < N; i++) {
        if (arr[i] % 2 == 1) isOdd = !isOdd;
    }
    
    if (isOdd) {
        cout << "YES" << endl;
        splits.push_back(N);
        for (int i = 0; i < splits.size(); i++) {
            if (i != 0) cout << " ";
            cout << splits[i];
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int Q;
    cin >> Q;
    for (int i = 1; i <= Q; i++) solve();
    return 0;
}