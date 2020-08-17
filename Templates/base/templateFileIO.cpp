#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 100005;

int N;

void solve(int tn) {
    fin >> N;
    fout << "Case #" << tn << ": " << N << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}