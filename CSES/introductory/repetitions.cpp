#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string str;

int main() {
    cin >> str;
    int lastI = 0, answer = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != str[lastI]) lastI = i;
        answer = max(i-lastI+1, answer);
    }
    cout << answer << endl;
}