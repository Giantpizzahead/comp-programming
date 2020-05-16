#include <iostream>

using namespace std;

int main() {
    for (int a = 1; a < 1000; a++) {
        for (int b = 1; b < 1000; b++) {
            int c = 1000 - a - b;
            if (c <= 0) continue;

            int sum = a * a + b * b;
            if (sum == c * c) {
                // Found!
                cout << a * b * c << endl;
            }
        }
    }
    return 0;
}
