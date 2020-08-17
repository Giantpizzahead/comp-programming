#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const int GUESSES = 999;

struct Query {
    int i, v, n;
};

int N, start, X;
vector<Query> queries;

int getRand(int maxNum) {
    return abs(rand() * rand()) % maxNum;
}

int main() {
    cin >> N >> start >> X;
    cout << "? " << start << endl;
    cout.flush();
    int value, next;
    cin >> value >> next;
    queries.push_back({start, value, next});
    srand(time(NULL));
    // Guess random locations
    for (int i = 0; i < GUESSES; i++) {
        int queryI = getRand(N) + 1;
        cout << "? " << queryI << endl;
        cout.flush();
        cin >> value >> next;
        queries.push_back({queryI, value, next});
    }
    // Sort in order of increasing value, then increasing index
    sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        if (a.v == b.v) return a.i < b.i;
        else return a.v < b.v;
    });
    /*
    for (int i = 0; i < queries.size(); i++) {
        cout << queries[i].i << " " << queries[i].n << " " << queries[i].v << endl;
    }
    */
    // Traverse singly linked list from closest starting point
    int startLoc = 0;
    for (; startLoc < queries.size(); startLoc++) {
        if (queries[startLoc].v >= X) break;
    }
    // Start before first >=
    startLoc--;
    if (startLoc == -1) startLoc = 0;
    int currLoc = queries[startLoc].i;
    while (true) {
        cout << "? " << currLoc << endl;
        cout.flush();
        cin >> value >> next;
        if (value >= X) {
            // Found the value
            cout << "! " << value << endl;
            cout.flush();
            return 0;
        } else if (next == -1) {
            // End of list reached
            cout << "! -1" << endl;
            cout.flush();
            return 0;
        } else {
            // Keep going
            currLoc = next;
        }
    }
}