/*
Solution: The key thing in this problem is that there will be a max of 6 square roots before a #
will become (and stay at) 1. So, just store all 6 sums in each node of a segment tree (0 sqrts,
1 sqrt, ... 5 sqrts), since the >=6th sqrt will always have a total sum of (# elements in node
range). These sums can be calculated by combining the sums of the child nodes (leaf nodes can
calc sum via original element).
To modify a range [a, b] to square root, do a normal segment tree traversal. When you get to the
target node, recalculate the square root sums by moving them up by 1, replacing the 6th sum (for
5 sqrts) with (# of elements in node range). Also keep a delta with how many times that range has
been sqrted. When moving back up, combine the child sums to get the new square root sums.
To propagate a square root, move all square root sums of the child nodes by the right amount,
then prop the delta value to both children.

Runtime: O(6M * log(N))
*/

#include <iostream>
#include <algorithm>
#include <math.h>

#define MAXN 100000
#define MAX_SQRT 7

using namespace std;

class SegmentTree {
public:
    int size;
    long* origArr;
    long* vals = new long[(MAXN * 4 + 1) * MAX_SQRT];
    int currSqrt[MAXN * 4 + 1], lazySqrt[MAXN * 4 + 1];
    
    SegmentTree(int size) : size(size) {}

    inline int index(int i, int j) {
        return i * MAX_SQRT + j;
    }

    void stsqrt(int low, int high) {
        if (low > high) stsqrt(1, 0, size - 1, high, low);
        else stsqrt(1, 0, size - 1, low, high);
    }

    void stsqrt(int n, int lb, int ub, int low, int high) {
        if (lb > high || ub < low) return;  // Out of range
        else if (lb >= low && ub <= high) {
            // Completely in range
            currSqrt[n]++;
            lazySqrt[n]++;
            return;
        } else {
            // Propagate
            propagate(n);

            // Partially in range; recurse and update
            stsqrt(n*2, lb, (lb+ub)/2, low, high);
            stsqrt(n*2+1, (lb+ub)/2+1, ub, low, high);

            // Update sums to sum of child nodes
            for (int j = 0; j < MAX_SQRT - currSqrt[n]; j++) {
                int leftJ = min(currSqrt[n*2] + j, MAX_SQRT - 1);
                int rightJ = min(currSqrt[n*2+1] + j, MAX_SQRT - 1);
                vals[index(n, currSqrt[n] + j)] = vals[index(n*2, leftJ)] + vals[index(n*2+1, rightJ)];
            }
        }
    }

    long query(int low, int high) {
        if (low > high) return query(1, 0, size - 1, high, low);
        else return query(1, 0, size - 1, low, high);
    }

    long query(int n, int lb, int ub, int low, int high) {
        if (lb > high || ub < low) return 0;  // Out of range
        else if (lb >= low && ub <= high) return vals[index(n, min(currSqrt[n], MAX_SQRT - 1))];  // Completely in range
        else {
            // Propagate
            propagate(n);
            return query(n*2, lb, (lb+ub)/2, low, high) + query(n*2+1, (lb+ub)/2+1, ub, low, high);
        }
    }

    void propagate(int n) {
        currSqrt[n*2] += lazySqrt[n];
        currSqrt[n*2+1] += lazySqrt[n];
        lazySqrt[n*2] += lazySqrt[n];
        lazySqrt[n*2+1] += lazySqrt[n];
        lazySqrt[n] = 0;
    }

    void initTree(int n, int lb, int ub) {
        // cout << n << " " << lb << " " << ub << endl;
        currSqrt[n] = 0;
        lazySqrt[n] = 0;
        if (lb == ub) {
            vals[index(n, 0)] = origArr[lb];
            // cout << "Element " << lb << ": " << vals[index(n, 0)] << endl;
            // Calculate all square roots
            for (int j = 1; j < MAX_SQRT; j++) {
                vals[index(n, j)] = sqrt(vals[index(n, j-1)]);
                // cout << vals[n][j] << endl;
            }
        } else {
            initTree(n * 2, lb, (lb + ub) / 2);
            initTree(n * 2 + 1, (lb + ub) / 2 + 1, ub);
            // Update sums
            for (int j = 0; j < MAX_SQRT; j++) {
                vals[index(n, j)] = vals[index(n*2, j)] + vals[index(n*2+1, j)];
            }
        }
    }

    /*
    long doSqrt(long v) {
        long low = 0;
        long high = 1000000000;
        while (low < high) {
            long mid = (low + high + 1) / 2;
            if (mid * mid <= v) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
    */
};

int N, M;
long arr[MAXN];

int main() {
    int caseNum = 0;
    // Make segment tree
    SegmentTree st(MAXN);
    while (scanf("%d", &N) != EOF) {
        // Process test case
        caseNum++;
        for (int i = 0; i < N; i++) scanf("%ld", &arr[i]);
        // Init segment tree
        st.origArr = arr;
        st.size = N;
        st.initTree(1, 0, N-1);
        // Handle queries
        scanf("%d", &M);
        printf("Case #%d:\n", caseNum);
        for (int i = 0; i < M; i++) {
            int type;
            scanf("%d", &type);
            int a, b;
            scanf("%d", &a);
            scanf("%d", &b);
            a--;
            b--;
            if (type) {
                // Query
                st.query(a, b);
                printf("%ld\n", st.query(a, b));
            } else {
                // Sqrt
                st.stsqrt(a, b);
                // cout << "Elements: ";
                // for (int i = 0; i < N; i++) cout << st.query(i, i) << " ";
                // cout << endl;
            }
        }
       printf("\n");
    }
}