#include <iostream>

using I = int;
using B = bool;

char s[50];
I p = 0, m = -1;
I c[] {-9, 9, -1, 1};
I C[] {85, 68, 76, 82};
B u[81];

B f(I i) {
    u[i] = 1;
    B Q = s[++m] == '?';

    if (i == 64) {
        m == 48 && p++;
        goto E;
    }

    for (I k = 0; k < 8; k++) {
        I K = k % 4;
        I N = i + c[K];
        B T = s[m] == C[K];
        if (k < 4 & !u[N] & u[N-9] + u[N+9] + u[N-1] + u[N+1] > 2) {
            Q | T && f(N);
            goto E;
        }
        Q | T && k > 3 & !u[N] && f(N);
    }

    E:
    u[i] = 0;
    m--;
}

I main() {
    std::cin >> s;
    for (I i = 0; i < 9; i++) {
        u[i] = 1;
        u[72+i] = 1;
        u[i*9] = 1;
        u[i*9+8] = 1;
    }
    u[63] = 0;
    u[73] = 0;
    f(10);
    printf("%d\n", p);
}