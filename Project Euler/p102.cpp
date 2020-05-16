#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("p102_triangles.txt");
string token;

void getToken() {
    getline(fin, token, ',');
}

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1) * (y3-y1) - (y2-y1) * (x3-x1);
}

int main() {
    int answer = 0;
    int x1, y1, x2, y2, x3, y3;
    for (int i = 0; i < 1000; i++) {
        getToken();
        x1 = stoi(token);
        getToken();
        y1 = stoi(token);
        getToken();
        x2 = stoi(token);
        getToken();
        y2 = stoi(token);
        getToken();
        x3 = stoi(token);
        getline(fin, token, '\n');
        y3 = stoi(token);

        int a = ccw(0, 0, x1, y1, x2, y2);
        int b = ccw(0, 0, x2, y2, x3, y3);
        int c = ccw(0, 0, x3, y3, x1, y1);
        if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0)) answer++;
    }
    cout << answer << endl;
}
