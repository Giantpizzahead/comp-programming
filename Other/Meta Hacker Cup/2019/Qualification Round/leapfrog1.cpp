#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

using namespace std;

void solve(int tn) {
    string str;
    fin >> str;
    int N = str.size() - 1;
    int numB = 0;
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == 'B') numB++;
    }

    bool possible = true;
    if (numB < (N + 1) / 2) possible = false;
    if (numB == N) possible = false;
    fout << "Case #" << tn << ": " << (possible ? 'Y' : 'N') << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}