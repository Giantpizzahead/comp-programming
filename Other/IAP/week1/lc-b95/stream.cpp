/**
 * Problem link:
 * https://leetcode.com/contest/biweekly-contest-95/problems/find-consecutive-integers-from-a-data-stream/
 */

#include <bits/stdc++.h>
using namespace std;

class DataStream {
public:
    int value, k, numConsec;
    DataStream(int value, int k) : value(value), k(k), numConsec(0) {}
    
    bool consec(int num) {
        if (num != value) numConsec = 0;
        else numConsec++;
        return numConsec >= k;
    }
};

// For debugging; leave this part out when submitting
int main() {
    DataStream dataStream(4, 3);
    cout << dataStream.consec(4) << '\n';
    cout << dataStream.consec(4) << '\n';
    cout << dataStream.consec(4) << '\n';
    cout << dataStream.consec(3) << '\n';
    return 0;
}
