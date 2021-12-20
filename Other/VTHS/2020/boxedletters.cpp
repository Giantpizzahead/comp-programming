#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 75005, MAXL = 12;

int N;
string dict[MAXN];
int side[26];
char letters[MAXL];

struct Edge {
    int endNode;
    int usedMask;
    int dictI;
};

vector<Edge> adj[MAXL];

struct State {
    int n, mask;
};

int fromNode[1 << MAXL][MAXL], fromWord[1 << MAXL][MAXL], fromMask[1 << MAXL][MAXL];
bool visited[1 << MAXL][MAXL];
queue<State> q;
stack<string> answer;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> dict[i];
    }
    for (int i = 0; i < 26; i++) side[i] = -1;
    char c;
    cin >> c; side[c-'A'] = 0; letters[0] = c;
    cin >> c; side[c-'A'] = 1; letters[1] = c;
    cin >> c; side[c-'A'] = 2; letters[2] = c;
    cin >> c; side[c-'A'] = 3; letters[3] = c;
    cin >> c; side[c-'A'] = 6; letters[6] = c;
    cin >> c; side[c-'A'] = 4; letters[4] = c;
    cin >> c; side[c-'A'] = 7; letters[7] = c;
    cin >> c; side[c-'A'] = 5; letters[5] = c;
    cin >> c; side[c-'A'] = 8; letters[8] = c;
    cin >> c; side[c-'A'] = 9; letters[9] = c;
    cin >> c; side[c-'A'] = 10; letters[10] = c;
    cin >> c; side[c-'A'] = 11; letters[11] = c;
    
    // Map all words to the puzzle (divided by 3 gives side)
    for (int i = 0; i < N; i++) {
        int startNode = side[dict[i][0]-'A'];
        if (startNode == -1) continue;
        int currNode = startNode;
        int usedMask = (1 << startNode);
        bool valid = true;
        for (int j = 1; j < dict[i].size(); j++) {
            int betweenNode = side[dict[i][j]-'A'];
            if (betweenNode == -1 || currNode / 3 == betweenNode / 3) {
                // Same side used twice
                valid = false;
                break;
            }
            usedMask |= (1 << betweenNode);
            currNode = betweenNode;
        }
        if (!valid) continue;
        int endNode = currNode;
        adj[startNode].push_back({endNode, usedMask, i});
    }

    // Start first word with any of the letters
    for (int i = 0; i < MAXL; i++) {
        fromNode[0][i] = -1;
        fromWord[0][i] = -1;
        visited[0][i] = true;
        q.push({i, 0});
    }
    while (!q.empty()) {
        auto ptr = q.front();
        int n = ptr.n, mask = ptr.mask;
        q.pop();
        if (mask == (1 << MAXL) - 1) {
            // Target found; rebuild words
            while (fromNode[mask][n] != -1) {
                answer.push(dict[fromWord[mask][n]]);
                int oldMask = fromMask[mask][n];
                int oldN = fromNode[mask][n];
                mask = oldMask;
                n = oldN;
            }
            break;
        }
        for (Edge& e : adj[n]) {
            int newN = e.endNode;
            int newMask = mask | e.usedMask;
            if (visited[newMask][newN]) continue;
            visited[newMask][newN] = true;
            fromNode[newMask][newN] = n;
            fromWord[newMask][newN] = e.dictI;
            fromMask[newMask][newN] = mask;
            q.push({newN, newMask});
        }
    }

    while (!answer.empty()) {
        cout << answer.top() << '\n';
        answer.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}