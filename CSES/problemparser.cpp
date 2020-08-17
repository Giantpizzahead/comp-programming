#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("raw_problems.txt");
ofstream fout("problems.txt");

int N;
vector<string> problems;
vector<int> solved, total;

int main() {
    string str;
    while (getline(fin, str)) {
        problems.push_back(str);
        int s, t;
        char c;
        fin >> s >> c >> t;
        solved.push_back(s);
        total.push_back(t);
        fin.get();
    }
    
    N = problems.size();
    fout << N << endl;
    for (int i = 0; i < N; i++) {
        fout << "0 " << problems[i] << endl;
    }
    for (int i = 0; i < N; i++) {
        fout << solved[i] << " " << total[i] << endl;
    }
    return 0;
}