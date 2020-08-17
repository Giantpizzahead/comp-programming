#include <iostream>
#define R return
using namespace std;
using L = long long;

const L X = 9e5;

L N, q;
L H[X];

L W(L s, L n, L d) {
    R n * s + d * n * (n-1) / 2;
}

L A[X], D[X], C[X];

L M(L a, L b) {
    R a + b;
}

L P(L n, L o, L p) {
    if (C[n] != 0) {
        L y = n*2;
        L Y = (o+p)/2-o+1;
        A[y] += W(D[n], Y, C[n]);
        A[y+1] += W(D[n] + Y * C[n], p-((o+p)/2+1)+1, C[n]);
        D[y] += D[n];
        D[y+1] += D[n] + Y * C[n];
        C[y] += C[n];
        C[y+1] += C[n];
        D[n] = 0;
        C[n] = 0;
    }
}

L I(L n, L o, L p) {
    D[n] = 0;
    if (o == p) A[n] = H[o];
    else {
        I(n*2, o, (o+p)/2);
        I(n*2+1, (o+p)/2+1, p);
        A[n] = M(A[n*2], A[n*2+1]);
    }
}

L U(L n, L o, L p, L l, L r) {
    if (o > r | p < l) R 0;
    if (o >= l & p <= r) {
        A[n] += W(o-l+1, p-o+1, 1);
        D[n] += o-l+1;
        C[n]++;
        R 0;
    }
    P(n, o, p);
    U(n*2, o, (o+p)/2, l, r);
    U(n*2+1, (o+p)/2+1, p, l, r);
    A[n] = M(A[n*2], A[n*2+1]);
}

L Q(L n, L o, L p, L l, L r) {
    if (o > r | p < l) R 0;
    if (o >= l & p <= r) R A[n];
    P(n, o, p);
    R M(Q(n*2, o, (o+p)/2, l, r), Q(n*2+1, (o+p)/2+1, p, l, r));
}

int main() {
    cin >> N >> q;
    for (L i = 1; i <= N; i++) cin >> H[i];
    I(1, 0, N);

    L t, a, b;
    for (L i = 0; i < q; i++) {
        cin >> t >> a >> b;
        if (t == 1) U(1, 0, N, a, b);
        else cout << Q(1, 0, N, a, b) << '\n';
    }
    R 0;
}