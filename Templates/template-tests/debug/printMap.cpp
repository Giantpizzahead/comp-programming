#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int main() {
    map<int, int> myMap;
    myMap[1] = 101;
    myMap[2] = 202;
    myMap[5] = 505;

    unordered_map<int, int> myMap2;
    myMap2[2] = 4;
    myMap2[8] = 16;
    myMap2[5] = 10;

    multimap<int, int> myMap3;
    myMap3.insert({1, 10});
    myMap3.insert({1, 20});
    myMap3.insert({5, 50});

    {
        auto& printMap = myMap;
        cout << "{";
        bool printNotFirst = false;
        for (auto x : printMap) {
            if (printNotFirst) cout << ", ";
            printNotFirst = true;
            cout << x.first << ": " << x.second;
        }
        cout << "}" << endl;
    }

    {
        auto& printMap = myMap2;
        cout << "{";
        bool printNotFirst = false;
        for (auto x : printMap) {
            if (printNotFirst) cout << ", ";
            printNotFirst = true;
            cout << x.first << ": " << x.second;
        }
        cout << "}" << endl;
    }

    {
        auto& printMap = myMap3;
        cout << "{";
        bool printNotFirst = false;
        for (auto x : printMap) {
            if (printNotFirst) cout << ", ";
            printNotFirst = true;
            cout << x.first << ": " << x.second;
        }
        cout << "}" << endl;
    }
}