#include <iostream>
using namespace std;

const int MAXC = 15;
int N;
char arr[MAXC][MAXC];

int main() {
    for (int i = 0; i < MAXC; i++) {
        for (int j = 0; j < MAXC; j++) {
            arr[i][j] = '.';
        }
    }
    cin >> N;
    int x1, y1, x2, y2;
    for (int i = 0; i < N; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        for (int y = y1; y < y2; y++) {
            for (int x = x1; x < x2; x++) {
                arr[y][x] = '#';
            }
        }
    }

    for (int i = 0; i < MAXC; i++) {
        for (int j = 0; j < MAXC; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    return 0;
}