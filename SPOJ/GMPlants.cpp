/*
Solution: Keep a segment tree for each axis, tracking the # of plants that are red in
each axis. Formula for # red is (x1y0z0 + x0y1z0 + x0y0z1 + x1y1z1), where ab means
# of b colors in the range of coordinates with the a axis.

Runtime: O(3(N + Q) * log(N))
*/

#include <iostream>

#define MAXN 100000

using namespace std;

class SegmentTree {
public:
    int size;
    int *numOn;
    bool *lazy;
    SegmentTree() : size(MAXN) {
        numOn = new int[MAXN * 4 + 1];
        lazy = new bool[MAXN * 4 + 1];
    }

    void light(int i, int j) {
        light(1, 0, size-1, i, j);
    }

    void light(int n, int lb, int ub, int i, int j) {
        if (lb > j || ub < i) return;
        else if (lb >= i && ub <= j) {
            numOn[n] = (ub - lb + 1) - numOn[n];
            lazy[n] = !lazy[n];
            return;
        }

        propagate(n, lb, ub);

        light(n*2, lb, (lb+ub)/2, i, j);
        light(n*2+1, (lb+ub)/2+1, ub, i, j);

        update(n);
    }

    long query(int i, int j) {
        if (i > j) return query(1, 0, size-1, j, i);
        else return query(1, 0, size-1, i, j);
    }

    long query(int n, int lb, int ub, int i, int j) {
        if (lb > j || ub < i) return 0;
        else if (lb >= i && ub <= j) return numOn[n];
        
        propagate(n, lb, ub);

        return query(n*2, lb, (lb+ub)/2, i, j) + query(n*2+1, (lb+ub)/2+1, ub, i, j);
    }

    inline void propagate(int n, int lb, int ub) {
        if (lazy[n]) {
            numOn[n*2] = ((lb+ub)/2 - lb + 1) - numOn[n*2];
            numOn[n*2+1] = (ub - (lb+ub)/2) - numOn[n*2+1];
            lazy[n*2] = !lazy[n*2];
            lazy[n*2+1] = !lazy[n*2+1];
            lazy[n] = false;
        }
    }

    inline void update(int n) {
        numOn[n] = numOn[n*2] + numOn[n*2+1];
    }

    void resetTree() {
        resetTree(1, 0, size-1);
    }

    void resetTree(int n, int lb, int ub) {
        numOn[n] = 0;
        lazy[n] = false;
        if (lb != ub) {
            resetTree(n*2, lb, (lb+ub)/2);
            resetTree(n*2+1, (lb+ub)/2+1, ub);
        }
    }
};

int T, NX, NY, NZ, Q;
SegmentTree segx;
SegmentTree segy;
SegmentTree segz;

int main() {
    scanf("%d", &T);
    int type, i, j, x1, y1, z1, x2, y2, z2;
    long long xq, yq, zq, xn, yn, zn;
    for (int t = 0; t < T; t++) {
        scanf("%d %d %d %d", &NX, &NY, &NZ, &Q);
        segx.size = NX;
        segy.size = NY;
        segz.size = NZ;
        segx.resetTree();
        segy.resetTree();
        segz.resetTree();
        for (int q = 0; q < Q; q++) {
            scanf("%d", &type);
            if (type == 0) {
                // X light
                scanf("%d %d", &i, &j);
                segx.light(i, j);
            } else if (type == 1) {
                // Y light
                scanf("%d %d", &i, &j);
                segy.light(i, j);
            } else if (type == 2) {
                // Z light
                scanf("%d %d", &i, &j);
                segz.light(i, j);
            } else {
                // Cube query
                scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
                xq = segx.query(x1, x2), xn = x2 - x1 + 1 - xq;
                yq = segy.query(y1, y2), yn = y2 - y1 + 1 - yq;
                zq = segz.query(z1, z2), zn = z2 - z1 + 1 - zq;
                // printf("On: %ld %ld %ld\n", xq, yq, zq);
                // for (int ss = 0; ss < NY * 4 + 1; ss++) cout << segy.numOn[ss] << ' ';
                // cout << endl;
                long long answer = xq*yn*zn + yq*xn*zn + zq*xn*yn + xq*yq*zq;
                printf("%lld\n", answer);
            }
        }
    }
}