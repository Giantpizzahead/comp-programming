#include <iostream>

using namespace std;

int arr[3][4] {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

int main() {
    // ----- BEGIN TEMPLATE -----
    auto& printArr = arr;
    cout << "[";
    for (int i = 0; i < sizeof(printArr)/sizeof(*printArr); i++) {
        if (i != 0) cout << "," << endl << " ";
        for (int j = 0; j < sizeof(printArr[i])/sizeof(*printArr[i]); j++) {
            if (j != 0) cout << ", ";
            cout << printArr[i][j];
        }
    }
    cout << "]" << endl;
    // ----- END TEMPLATE -----
}