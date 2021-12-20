#include <iostream>
#include <algorithm>

using namespace std;

class Matrix {
public:
    long* arr;
    unsigned int rows, cols, rawSize;
    static const long MOD = 1000000007;

    Matrix(int rows, int cols) : rows(rows), cols(cols), rawSize(rows * cols) {
        arr = new long[rawSize];
        for (int i = 0; i < rawSize; i++) arr[i] = 0;
    }

    Matrix(const Matrix& other) {
        cout << "Copied...???" << endl;
    }

    ~Matrix() {
        delete[] arr;
    }

    long& at(int i, int j) const {
        checkBounds(i, j);
        return arr[i * cols + j];
    }

    static Matrix* Multiply(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows)
            cerr << "Invalid matrix sizes for multiplication!" << endl;
        
        Matrix* rPtr = new Matrix(a.rows, b.cols);
        Matrix& r = *rPtr;
        for (int i = 0; i < r.rows; i++) {
            for (int j = 0; j < r.cols; j++) {
                for (int k = 0; k < b.rows; k++) {
                    r.at(i, j) += a.at(i, k) * b.at(k, j);
                    r.at(i, j) %= MOD;
                }
            }
        }

        return rPtr;
    }

    void checkBounds(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            cerr << "Error: arr[" << i << "][" << j << "] is out of bounds!" << endl;
    }

    Matrix& operator*(const Matrix& other) const {
        return *Multiply(*this, other);
    }
};

ostream& operator<<(ostream& out, const Matrix& m) {
    cout << "Matrix:" << endl;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            out << m.at(i, j) << '\t';
        }
        out << endl;
    }
    return out;
}

int main() {
    Matrix m(26, 26);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            scanf("%ld", &m.at(i, j));
        }
    }

    // Precompute required matrices for matrix exponentiation
    Matrix* precomp[24];
    precomp[0] = &m;
    for (int i = 1; i < 24; i++) {
        precomp[i] = &((*precomp[i-1]) * (*precomp[i-1]));
    }

    int T, L;
    char C;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("\n%c", &C);
        scanf("%d", &L);
        // Compute test case using precomputed matrices
        Matrix result(1, 26);
        for (int j = 0; j < 26; j++) result.at(0, j) = 1;
        for (int j = 23; j >= 0; j--) {
            if (L > 1 << j) {
                L -= 1 << j;
                result = result * (*precomp[j]);
            }
        }
        printf("%ld\n", result.at(0, C - 'a'));
    }
}