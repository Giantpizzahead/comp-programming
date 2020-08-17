#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAXN 50

ifstream fin("input.txt");
ofstream fout("output.txt");

int N;
bool in_allowed[MAXN];
bool out_allowed[MAXN];
bool can_travel[MAXN][MAXN];

void solve(int tn) {
    fin >> N;
    string line;
    fin.get();
    getline(fin, line);
    for (int i = 0; i < N; i++) {
        in_allowed[i] = line[i] == 'Y';
    }
    getline(fin, line);
    for (int i = 0; i < N; i++) {
        out_allowed[i] = line[i] == 'Y';
    }
    // Reset array
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            can_travel[i][j] = false;
        }
    }
    // For each country, go as far left / right as possible
    for (int i = 0; i < N; i++) {
        can_travel[i][i] = true;
        for (int r = i+1; r < N; r++) {
            if (out_allowed[r-1] && in_allowed[r]) {
                can_travel[i][r] = true;
            } else break;
        }
        for (int l = i-1; l >= 0; l--) {
            if (out_allowed[l+1] && in_allowed[l]) {
                can_travel[i][l] = true;
            } else break;
        }
    }

    fout << "Case #" << tn << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fout << (can_travel[i][j] ? 'Y' : 'N');
        }
        fout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}
