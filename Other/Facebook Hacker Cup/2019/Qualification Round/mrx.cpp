#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

bool evaluate(string expr, bool x) {
    // cout << "evaluting " << expr << endl;
    if (expr[0] == '(') {
        int numParens = 0, cutLoc = -1;
        for (int i = 1; i < expr.size(); i++) {
            if (expr[i] == '(') numParens++;
            else if (expr[i] == ')') numParens--;
            else if (numParens == 0 && (expr[i] == '|' || expr[i] == '&' || expr[i] == '^')) {
                // Separator found
                cutLoc = i;
                break;
            }
        }
        string newExpr1 = expr.substr(1, cutLoc - 1);
        string newExpr2 = expr.substr(cutLoc + 1, expr.size() - cutLoc - 2);
        bool result1 = evaluate(newExpr1, x);
        bool result2 = evaluate(newExpr2, x);
        if (expr[cutLoc] == '|') return result1 || result2;
        else if (expr[cutLoc] == '&') return result1 && result2;
        else if (expr[cutLoc] == '^') return result1 != result2;
    } else if (expr[0] == '0') return false;
    else if (expr[0] == '1') return true;
    else if (expr[0] == 'x') return x;
    else if (expr[0] == 'X') return !x;
}

void solve(int tn) {
    string E;
    fin >> E;
    bool zeroResult = evaluate(E, false);
    bool oneResult = evaluate(E, true);

    bool same = zeroResult == oneResult;
    fout << "Case #" << tn << ": " << (same ? 0 : 1) << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}