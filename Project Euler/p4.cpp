#include <iostream>
#include <algorithm>

using namespace std;

bool ispalindrome(int n) {
    vector<int> digits;
    while (n != 0) {
        int d = n % 10;
        n /= 10;
        digits.push_back(d);
    }

    for (unsigned int i = 0; i < digits.size() / 2; i++) {
        if (digits[i] != digits[digits.size() - 1 - i]) return false;
    }
    return true;
}

int main() {
    int answer = 0;
    for (int a = 100; a < 1000; a++) {
        for (int b = 100; b < 1000; b++) {
            int n = a * b;
            if (ispalindrome(n)) answer = max(n, answer);
        }
    }
    cout << answer << endl;
    return 0;
}
