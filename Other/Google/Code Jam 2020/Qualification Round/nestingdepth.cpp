#include <iostream>

using namespace std;

void solve(int tn) {
    string str;
    getline(cin, str);

    cout << "Case #" << tn << ": ";

    int currDepth = 0;
    for (int i = 0; i < str.length(); i++) {
        int num = str[i] - '0';
        while (currDepth < num) {
            cout << '(';
            currDepth++;
        }
        while (currDepth > num) {
            cout << ')';
            currDepth--;
        }
        cout << str[i];
    }
    while (currDepth > 0) {
        cout << ')';
        currDepth--;
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    cin.get();
    for (int i = 1; i <= T; i++) solve(i);
    return EXIT_SUCCESS;
}
