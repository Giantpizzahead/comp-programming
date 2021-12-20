#include <iostream>

using namespace std;

int arr[] {1, 2, 3, 4, 5};

int main() {
    // ----- BEGIN TEMPLATE -----
    auto& printArr = arr;
    cout << "[";
    for (int i = 0; i < sizeof(printArr)/sizeof(*printArr); i++) {
        if (i != 0) cout << ", ";
        cout << printArr[i];
    }
    cout << "]" << endl;
    // ----- END TEMPLATE -----
}