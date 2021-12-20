#include <iostream>

#define MAXB 110

using namespace std;

int q, B;
int arr[MAXB];

int query(int i);
void doComp();
void doRev();

/**
Guaranteed to use 2 queries on every call (to maintain even # of bits found).
**/
void fixArray() {
    // 1 = Bits were the same (1010), 2 = Bits were different (1100)
    bool type1Done = false, type2Done = false;
    bool comp = true, rev = true, both = true, none = true;
    for (int i = 0; i < B / 2; i++) {
        if (arr[i] == -1 || arr[B-1-i] == -1) break;  // Bits haven't been explored yet
        if (arr[i] == arr[B-1-i] && !type1Done) {
            type1Done = true;
            int l = query(i);
            if (l == arr[i]) {
                // Bit stayed the same
                comp = false;
                both = false;
            } else {
                // Bit is now different
                rev = false;
                none = false;
            }
        } else if (arr[i] != arr[B-1-i] && !type2Done) {
            type2Done = true;
            int l = query(i);
            if (l == arr[i]) {
                // Bit stayed the same
                comp = false;
                rev = false;
            } else {
                // Bit is now different
                both = false;
                none = false;
            }
        }
    }

    // Use 2 queries no matter what
    if (!type1Done) query(0);
    if (!type2Done) query(0);

    // Fix the array
    if (none) return;
    else if (comp) {
        doComp();
    } else if (rev) {
        doRev();
    } else if (both) {
        doComp();
        doRev();
    } else {
        // cerr << "Nothing possible!" << endl;
    }
}

void doComp() {
    for (int i = 0; i < B; i++) {
        if (arr[i] != -1) arr[i] = 1 - arr[i];
    }
}

void doRev() {
    for (int i = 0; i < B / 2; i++) {
        int t = arr[i];
        arr[i] = arr[B - 1 - i];
        arr[B - 1 - i] = t;
    }
}

bool solve(int tn) {
    for (int i = 0; i < B; i++) arr[i] = -1;

    q = 1;
    for (int i = 0; i < B; i++) {
        if (q % 10 == 1) {
            // Figure out what happened
            // cerr << "Num found: " << i << endl;
            fixArray();
        }
        // Find next bit
        if (i % 2 == 0) arr[i/2] = query(i/2);
        else arr[B - 1 - i/2] = query(B - 1 - i/2);
    }

    for (int i = 0; i < B; i++) cout << arr[i];
    cout << endl;

    char c;
    cin >> c;
    return c == 'Y';
}

int query(int i) {
    q++;
    cout << i+1 << endl;
    // cerr << "query " << i+1 << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    int T;
    cin >> T >> B;
    for (int i = 1; i <= T; i++) {
        if (!solve(i)) return 1;
    }
    return 0;
}
