#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

void solve(int tn) {
    long long X;
    fin >> X;
    int answer = 0;
    for (ll a = 0;; a++) {
        ll remaining = X - a * a;
        ll b = round(sqrt(remaining));
        if (a > b) break;
        if (b * b == remaining) {
            answer++;
        }
        // cout << sqrt(remaining) << endl;
    }
    fout << "Case #" << tn << ": " << answer << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}