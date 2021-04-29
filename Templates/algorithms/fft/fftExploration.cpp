//#define NDEBUG
#include <assert.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <initializer_list>
#include <complex>
#include <cmath>

const int MOD = 1000000007;

/**
 * Polynomials have a degree D and D+1 coefficients. C[i] is the coefficient of the term with degree i.
 */
class Polynomial {
private:
    int D;
    std::vector<int> C;

public:
    Polynomial() : D(0), C(1) {}

    /**
     * Creates a Polynomial with the given degree, all coefficients start as 0.
     */
    Polynomial(int degree) : D(degree), C(degree+1) {
        assert(D >= 0);
    }

    /**
     * Creates a Polynomial using the given coefficients.
     */
    Polynomial(std::vector<int> startC) : D(startC.size()-1), C(startC) {
        assert(D >= 0);
    }

    /**
     * Creates a Polynomial using the given coefficients.
     */
    Polynomial(std::initializer_list<int> list) : D(list.size()-1), C(list) {
        assert(D >= 0);
    }

    Polynomial(const Polynomial& P) : D(P.D), C(P.C) {}

    ~Polynomial() {}

    /**
     * Evaluates the polynomial at the given value.
     */
    int eval(int x) {
        long long r = 0, powX = 1;
        for (int i = 0; i <= D; i++) {
            r = (r + C[i] * powX) % MOD;
            powX = powX * x % MOD;
        }
        return (r % MOD + MOD) % MOD;
    }

    /**
     * New coefficients are set to 0 by default, and old ones are truncated if needed.
     */
    void setDeg(int degree) {
        assert(degree >= 0);
        D = degree;
        C.resize(D+1);
    }

    int deg() const {
        return D;
    }

    int& operator[](int i) {
        assert(i >= 0 && i <= D);
        return C[i];
    }

    const int& operator[](int i) const {
        assert(i >= 0 && i <= D);
        return C[i];
    }
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    /*
    for (int i = p.deg(); i >= 0; i--) {
        if (i != p.deg()) {
            if (p[i] >= 0) os << " + ";
            else os << " - ";
        } else if (p[i] < 0) os << "-";
        os << abs(p[i]) << "x^" << i;
    }
    */
    /**/
    bool first = true;
    for (int i = p.deg(); i >= 0; i--) {
        if (p[i] == 0) continue;
        if (!first) {
            if (p[i] > 0) os << " + ";
            else os << " - ";
        } else if (p[i] < 0) os << "-";
        int v = abs(p[i]);
        if (i == 0 || v != 1) os << v;
        if (i != 0) {
            os << "x";
            if (i != 1) os << "^" << i;
        }
        first = false;
    }
    if (first) os << "0";
    /**/
    return os;
}

/**
 * The BasePolyMult abstract class contains a method that can multiply two Polynomials.
 */
class BasePolyMult {
public:
    virtual Polynomial polyMult(Polynomial& A, Polynomial& B) = 0;
};

/**
 * Uses the distributive property.
 * Runtime: O(N^2 * Q)
 */
class NaivePolyMult : public BasePolyMult {
public:
    Polynomial polyMult(Polynomial& A, Polynomial& B) {
        Polynomial C(A.deg()+B.deg());
        for (int i = 0; i <= A.deg(); i++) {
            for (int j = 0; j <= B.deg(); j++) {
                C[i+j] = (C[i+j] + (long long) A[i] * B[j]) % MOD;
            }
        }
        return C;
    }
};






















/**
 * Uses the Fast Fourier Transform.
 * Runtime: ?
 */
class FFTPolyMult : public BasePolyMult {
private:
    using complex = std::complex<double>;

    complex eval(std::vector<complex> P, complex x) {
        complex r = 0, powX = 1;
        for (int i = 0; i < P.size(); i++) {
            r = (r + powX * P[i]);
            powX = powX * x;
        }
        return r;
    }

    std::vector<complex> FFT(std::vector<complex> P) {
        // std::cout << "FFT ";
        // for (complex x : P) std::cout << x << ", ";
        // std::cout << std::endl;

        int N = P.size();
        // For now, just evaluate the points
        std::vector<complex> answer(N);
        for (int i = 0; i < N; i++) {
            complex x = std::polar(1.0, M_PI * 2 * i / N);
            answer[i] = eval(P, x);
        }

        // std::cout << "result = ";
        // for (complex x : answer) std::cout << x << ", ";
        // std::cout << std::endl;
        return answer;
    }

    std::vector<complex> IFFT(std::vector<complex> P) {
        // std::cout << "IFFT ";
        // for (complex x : P) std::cout << x << ", ";
        // std::cout << std::endl;

        int N = P.size();
        // For now, just evaluate the points
        std::vector<complex> answer(N);
        for (int i = 0; i < N; i++) {
            complex x = std::polar(1.0, -M_PI * 2 * i / N);
            answer[i] = eval(P, x) / (double) N;
        }

        // std::cout << "result = ";
        // for (complex x : answer) std::cout << x << ", ";
        // std::cout << std::endl;
        return answer;
    }

public:
    Polynomial polyMult(Polynomial& tempA, Polynomial& tempB) {
        // Resize both polynomials to the same power of two
        int numPoints = 1;
        while (numPoints <= std::max(tempA.deg(), tempB.deg())) numPoints *= 2;
        numPoints *= 2;
        std::vector<complex> A(numPoints), B(numPoints);
        for (int i = 0; i <= tempA.deg(); i++) A[i] = tempA[i];
        for (int i = 0; i <= tempB.deg(); i++) B[i] = tempB[i];

        // Evaluate both polynomials at points
        std::vector<complex> pointsA = FFT(A);
        std::vector<complex> pointsB = FFT(B);
        // Combine points
        std::vector<complex> pointsC(numPoints);
        for (int i = 0; i < numPoints; i++) {
            pointsC[i] = pointsA[i] * pointsB[i];
        }
        
        // Convert points back to polynomial
        std::vector<complex> coeffs = IFFT(pointsC);
        Polynomial C(coeffs.size()-1);
        for (int i = 0; i < coeffs.size(); i++) {
            C[i] = (long long) std::round(coeffs[i].real()) % MOD;
        }
        return C;
    }
};

















bool tryMult(Polynomial& A, Polynomial& B, BasePolyMult& polyMult) {
    Polynomial C = polyMult.polyMult(A, B);
    // Test correctness
    bool correct = true;
    for (int x = -5; x <= 5; x++) {
        if ((long long) A.eval(x) * B.eval(x) % MOD != C.eval(x)) {
            correct = false;
            break;
        }
    }

    std::cout << (correct ? "[✓] " : "[✗] ");
    std::cout << "(" << A << ") * (" << B << ") = " << C;
    std::cout << std::endl;
    return correct;
}

void manualTest() {
    FFTPolyMult fft;

    Polynomial A = {-8, 1}, B = {8, 1};
    tryMult(A, B, fft);

    A = {0, -2, 3}, B = {5, 0, 1};
    tryMult(A, B, fft);
}

std::random_device rd;
std::mt19937 gen(rd());

int randInt(int a, int b) {
    return gen() % (b-a+1) + a;
}

Polynomial genRandomPoly(int deg, int range) {
    Polynomial P(deg);
    for (int i = 0; i <= deg; i++) P[i] = randInt(-range, range);
    return P;
}

void stressTest(int N, int R, int Q, BasePolyMult& polyMult, std::string name, bool debug = false) {
    auto startTime = std::chrono::steady_clock::now();

    bool correct = true;
    for (int i = 0; i < Q; i++) {
        Polynomial A = genRandomPoly(randInt(0, N), randInt(0, R));
        Polynomial B = genRandomPoly(randInt(0, N), randInt(0, R));
        if (debug) {
            correct &= tryMult(A, B, polyMult);
        } else {
            Polynomial C = polyMult.polyMult(A, B);
        }
    }

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    std::cout << (correct ? "[✓] " : "[✗] ") << name << ": " << duration.count() << "s";
    std::cout << std::endl;
}

int main() {
    std::cout << std::fixed;
    manualTest();
    NaivePolyMult naive;
    FFTPolyMult fft;
    // stressTest(300, 1000000000, 300, naive, "naive", false);
    stressTest(5, 10, 5, fft, "fft", true);
    return 0;
}