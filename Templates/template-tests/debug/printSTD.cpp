#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    v.push_back(8);

    set<int> s;
    s.insert(1);
    s.insert(5);
    s.insert(10);

    {
        auto& printSTD = v;
        cout << "[";
        bool printNotFirst = false;
        for (auto val : printSTD) {
            if (printNotFirst) cout << ", ";
            printNotFirst = true;
            cout << val;
        }
        cout << "]" << endl;
    }

    {
        auto& printSTD = s;
        cout << "[";
        bool printNotFirst = false;
        for (auto val : printSTD) {
            if (printNotFirst) cout << ", ";
            printNotFirst = true;
            cout << val;
        }
        cout << "]" << endl;
    }
}