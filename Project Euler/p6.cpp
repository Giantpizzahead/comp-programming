#include <iostream>

using namespace std;

int main() {
    long long A = 0, B = 0;
    for (int i = 1; i <= 100; i++) {
        A += i * i;
        B += i;
    }
    B *= B;

    cout << B - A << endl;
}
