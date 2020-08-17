#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAXN 800000

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Tree {
    int p, h;
};

int N;
Tree trees[MAXN];
unordered_map<int, int> going_right, going_left;

void solve(int tn) {
    going_left.clear();
    going_right.clear();

    // cout << "----------" << endl;
    fin >> N;
    int p, h;
    for (int i = 0; i < N; i++) {
        fin >> p >> h;
        trees[i] = {p, h};
    }
    // Sort trees in order of increasing position
    sort(trees, trees+N, [](Tree& a, Tree& b) {
        return a.p < b.p;
    });

    // Calculate longest chains ending at a location if all trees fall to the right
    for (int i = 0; i < N; i++) {
        // cout << trees[i].p << ' ' << trees[i].h << endl;
        unordered_map<int, int>::iterator ptr = going_right.find(trees[i].p);
        int longest = (ptr == going_right.end()) ? 0 : ptr->second;

        // Add new value if this tree fell to the right
        ptr = going_right.find(trees[i].p + trees[i].h);
        if (ptr == going_right.end()) {
            going_right.emplace(trees[i].p + trees[i].h, longest + trees[i].h);
        } else {
            ptr->second = max(longest + trees[i].h, ptr->second);
        }
    }
    // Do the same thing for going left
    for (int i = N-1; i >= 0; i--) {
        unordered_map<int, int>::iterator ptr = going_left.find(trees[i].p);
        int longest = (ptr == going_left.end()) ? 0 : ptr->second;

        // Add new value if this tree fell to the left
        ptr = going_left.find(trees[i].p - trees[i].h);
        if (ptr == going_left.end()) {
            going_left.emplace(trees[i].p - trees[i].h, longest + trees[i].h);
        } else {
            ptr->second = max(longest + trees[i].h, ptr->second);
        }
    }

    // Try each meeting point (falling from left and right) to find the optimal one
    int answer = 0;
    for (const pair<int, int>& p : going_right) {
        unordered_map<int, int>::const_iterator ptr = going_left.find(p.first);
        int longest = (ptr == going_left.end()) ? 0 : ptr->second;
        answer = max(p.second + longest, answer);
    }
    for (const pair<int, int>& p : going_left) {
        unordered_map<int, int>::const_iterator ptr = going_right.find(p.first);
        int longest = (ptr == going_right.end()) ? 0 : ptr->second;
        answer = max(p.second + longest, answer);
    }

//    for (auto const& p : going_left) {
//        cout << p.first << " " << p.second << endl;
//    }

    fout << "Case #" << tn << ": " << answer << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}
