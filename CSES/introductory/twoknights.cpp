#include <iostream>
using l = long long;

l N;

void p(l x) {
    std::cout << x << '\n';
}

int main() {
    std::cin >> N;
    p(0);
    if (N > 1) p(6);
    if (N > 2) p(28);
    for (l i = 4; i <= N; i++) {
        l choose2 = (i*i) * (i*i-1);
        l o = 8 + 3 * 8 + 16;
        o += (i-4) * 4 * 4;
        o += (i-4) * 4 * 6;
        o += (i-4) * (i-4) * 8;
        l a = (choose2-o) / 2;
        p(a);
    }
}