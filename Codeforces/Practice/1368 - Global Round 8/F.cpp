#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1005;

int N;
bool target[MAXN], on[MAXN];
vector<int> moves;

int main() {
    cin >> N;
    // Try all strategies
    if (N <= 3) {
        cout << 0 << endl;
        return 0;
    }
    int bestK = 0, bestL = 0;
    for (int i = 2; i < N; i++) {
        int currL = 0, currI = 0;
        while (currI < N-1) {
            for (int j = 1; j < i; j++) {
                currL++;
                currI++;
                if (currI == N-1) break;
            }
            currI++;
        }
        currL -= (i-1);
        // cout << "strat " << i << " = " << currL << endl;
        if (currL > bestL) {
            bestK = i;
            bestL = currL;
        }
    }

    // cout << "best = " << bestK << endl;

    // Apply best strategy
    int currI = 0;
    while (currI < N-1) {
        for (int j = 1; j < bestK; j++) {
            target[currI] = true;
            currI++;
            if (currI == N-1) break;
        }
        currI++;
    }

    while (true) {
        bool broke = false;
        moves.clear();
        for (int i = 0; i < N; i++) {
            if (!on[i] && target[i]) {
                if (moves.size() == bestK) {
                    broke = true;
                    break;
                }
                moves.push_back(i+1);
                on[i] = true;
            }
        }
        cout << moves.size();
        for (int x : moves) cout << " " << x;
        cout << endl;
        if (!broke) {
            // Optimal reached
            cout << 0 << endl;
            return 0;
        }
        int resp;
        cin >> resp;
        if (resp == -1) return 0;
        // Turn off selected lamps
        resp--;
        for (int i = 0; i < bestK; i++) {
            on[resp] = false;
            resp = (resp + 1) % N;
        }

        // cout << "on: ";
        // for (int i = 0; i < N; i++) cout << on[i];
        // cout << endl;
        // cout << "target: ";
        // for (int i = 0; i < N; i++) cout << target[i];
        // cout << endl;
    }
    return 0;
}