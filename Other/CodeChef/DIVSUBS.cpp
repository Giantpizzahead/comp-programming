#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1e5+5;

int N;
vector<int> nums[MAXN];
pair<int, int> pairs[MAXN];

void solve() {
    if (!nums[0].empty()) {
        cout << 1 << endl;
        cout << nums[0][0] << endl;
        return;
    }
    // Check for pairs
    for (int i = 1; i < N; i++) {
        int currNum = 0;
        for (int j = 1; j <= nums[i].size(); j++) {
            currNum = (currNum + i) % N;
            if (currNum == 0) {
                // Output this
                cout << j << endl;
                for (int k = 0; k < j; k++) {
                    if (k != 0) cout << ' ';
                    cout << nums[i][k];
                }
                cout << endl;
                return;
            } else if (pairs[N-currNum].first != 0) {
                // Pair found; output it
                cout << j + pairs[N-currNum].first << endl;
                for (int k = 0; k < pairs[N-currNum].first; k++) {
                    if (k != 0) cout << ' ';
                    cout << nums[pairs[N-currNum].second][k];
                }
                for (int k = 0; k < j; k++) {
                    cout << ' ';
                    cout << nums[i][k];
                }
                cout << endl;
                return;
            }
        }
        // Add found pairs
        currNum = 0;
        for (int j = 1; j <= nums[i].size(); j++) {
            currNum = (currNum + i) % N;
            pairs[currNum].first = j;
            pairs[currNum].second = i;
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            pairs[i].first = 0;
            pairs[i].second = 0;
            nums[i].clear();
        }
        int x;
        for (int i = 0; i < N; i++) {
            cin >> x;
            x %= N;
            nums[x].push_back(i+1);
        }
        solve();
    }
}