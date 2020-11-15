#include <iostream>
#include <fstream>

using namespace std;

ofstream fout("output2.txt");

int main() {
    fout << "5\n";
    for (int j = 0; j < 5; j++) {
        fout << "500000 1 1\n";
        for (int i = 1; i < 500000; i++) {
            if (i != 0) fout << ' ';
            fout << i;
        }
        fout << '\n';
    }
    return 0;
}