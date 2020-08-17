#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 99999

ifstream fin("input.txt");
ofstream fout("output.txt");

void solve(int tn) {
    int N;
    fin >> N;
    fin.get();
    int a = 0, b = 0;
    for (int i = 0; i < N; i++) {
        if (fin.get() == 'A') a++;
        else b++;
    }
    fout << "Case #" << tn << ": " << ((a - b == 1 || b - a == 1) ? 'Y' : 'N') << "\n";
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
}
