#include <iostream>
#include <string>

using namespace std;
using ll = long long;

ll D, Q;

int main() {
    ios::sync_with_stdio(false);
    ll N;
    cin >> N >> Q;
    N++;
    while (N > 1) {
        N /= 2;
        D++;
    }
    ll U;
    string str;
    for (int i = 0; i < Q; i++) {
        cin >> U >> str;
        int currDepth = 0;
        for (int i = 0; i < D; i++) {
            if (U & (1LL << i)) {
                currDepth = D - i;
                break;
            }
        }
        for (char c : str) {
            // cout << U << " ";
            if (c == 'U') {
                // Decrease depth if possible
                if (currDepth != 1) {
                    U &= ~(1LL << (D - currDepth));
                    U |= (1LL << (D - currDepth + 1));
                    currDepth--;
                }
            } else if (c == 'R') {
                // Go to right child if possible
                if (currDepth != D) {
                    U |= (1LL << (D - currDepth - 1));
                    currDepth++;
                }
            } else {
                // Go to left child if possible
                if (currDepth != D) {
                    U &= ~(1LL << (D - currDepth));
                    U |= (1LL << (D - currDepth - 1));
                    currDepth++;
                }
            }
        }
        cout << U << endl;
    }
    return 0;
}