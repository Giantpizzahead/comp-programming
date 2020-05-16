#include <iostream>

using namespace std;

int main() {
    int sum = 0;

    int curr = 2, last = 1;
    while (curr <= 4000000) {
        if (curr % 2 == 0) sum += curr;
        int temp = curr + last;
        last = curr;
        curr = temp;
    }

    cout << sum << endl;
    return 0;
}
