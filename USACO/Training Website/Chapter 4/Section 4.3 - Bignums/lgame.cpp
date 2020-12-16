/*
ID: sunnyky1
LANG: C++11
TASK: lgame
*/

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

unordered_set<string> words;
int values[] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
string letters;
int best = 0;
string str;
bool used[7];
set<string> answers;

int getScore(string& x) {
    int S = 0;
    for (char c : x) {
        S += values[c - 'a'];
    }
    return S;
}

void tryCombo() {
    // One word
    int score;
    for (int x = 3; x <= letters.size(); x++) {
        score = 0;
        string a = str.substr(0, x);
        if (words.count(a)) {
            score = getScore(a);
            if (score > best) {
                best = score;
                answers.clear();
            }
            if (score == best) {
                answers.insert(a);
            }
        }
    }

    // Split into 3-4
    score = 0;
    string a = str.substr(0, 3);
    string b = str.substr(3, 4);
    if (words.count(a) && words.count(b)) {
        score = getScore(a) + getScore(b);
        if (score > best) {
            best = score;
            answers.clear();
        }
        if (score == best) {
            if (a < b) answers.insert(a + " " + b);
            else answers.insert(b + " " + a);
        }
    } 
    
    
    // Split into 3-3
    score = 0;
    a = str.substr(0, 3);
    b = str.substr(3, 3);
    if (words.count(a) && words.count(b)) {
        score = getScore(a) + getScore(b);
        if (score > best) {
            best = score;
            answers.clear();
        }
        if (score == best) {
            if (a < b) answers.insert(a + " " + b);
            else answers.insert(b + " " + a);
        }
    } 
}

void gen(int i) {
    if (i == letters.size()) {
        tryCombo();
        return;
    }
    for (int j = 0; j < letters.size(); j++) {
        if (!used[j]) {
            used[j] = true;
            str[i] = letters[j];
            gen(i+1);
            used[j] = false;
        }
    }
}

void solve() {
    cin >> letters;
    str.resize(letters.size());
    gen(0);
    cout << best << '\n';
    for (string s : answers) cout << s << '\n';
}

ifstream dictin("lgame.dict");

int main() {
    freopen("lgame.in", "r", stdin);
    freopen("lgame.out", "w", stdout);
    string str;
    while (true) {
        dictin >> str;
        if (str == ".") break;
        words.insert(str);
    }
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}