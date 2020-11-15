#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int N, M;
int counts[256];
vector<pair<int, char>> even, odd, tempEven, tempOdd;
vector<int> possible;
vector<char> centers;
stack<char> charStack;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> str;
    for (int i = 1; i <= N; i++) {
        if (N % i == 0) possible.push_back(i);
    }
    for (int i = 0; i < N; i++) {
        counts[str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (counts[i] != 0) {
            if (counts[i] % 2 == 0) even.push_back({counts[i], i});
            else odd.push_back({counts[i], i});
        }
    }

    sort(possible.begin(), possible.end(), greater<int>());

    for (int x : possible) {
        // cout << x << endl;
        int k = N / x;
        tempEven.clear();
        tempOdd.clear();
        centers.clear();
        for (pair<int, char>& t : even) tempEven.push_back({t.first, t.second});
        for (pair<int, char>& t : odd) tempOdd.push_back({t.first, t.second});

        if (x % 2 == 1) {
            // Odd length; convert to even
            if (k < tempOdd.size()) continue;  // Impossible
            int converted = tempOdd.size();
            for (pair<int, char>& t : tempOdd) {
                centers.push_back(t.second);
                t.first--;
                if (t.first != 0) tempEven.push_back(t);
                tempOdd.pop_back();
            }
            // Convert arbitrary evens to centers
            if ((k - converted) % 2 == 1) continue;  // Impossible
            for (int i = converted; i < k; i++) {
                pair<int, char>& p = tempEven[tempEven.size()-1];
                p.first--;
                centers.push_back(p.second);
                if (p.first == 0) tempEven.pop_back();
            }
            x--;
        }

        if (tempOdd.empty()) {
            // Possible!
            cout << k << endl;
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < x / 2; j++) {
                    pair<int, char>& p = tempEven[tempEven.size()-1];
                    p.first -= 2;
                    charStack.push(p.second);
                    cout << p.second;
                    if (p.first == 0) tempEven.pop_back();
                }
                if (!centers.empty()) {
                    cout << centers[centers.size()-1];
                    centers.pop_back();
                }
                while (!charStack.empty()) {
                    cout << charStack.top();
                    charStack.pop();
                }
                cout << (i == k-1 ? '\n' : ' ');
            }
            break;
        }
    }
    return 0;
}