#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 60;
const int MAXM = 120;

bool possible;
int N, M;
int X[MAXM], Y[MAXM], Z[MAXM];
int parents[MAXN];
vector<int> adj[MAXN];

void floodfill(int n, int st, int subtrees[]) {
    subtrees[n] = st;
    for (int e : adj[n]) {
        if (subtrees[e] == -1) floodfill(e, st, subtrees);
    }
}

void genTree(int parent, bool usingNode[]) {
    /*
    cout << "genTree(" << parent+1 << ", [";
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ", ";
        cout << (usingNode[i] ? 1 : 0);
    }
    cout << "])" << endl;
    */

    // Try making every node the root
    for (int root = 0; root < N; root++) {
        if (!usingNode[root]) continue;
        // Determine subtrees using floodfill
        int subtrees[MAXN];
        for (int i = 0; i < N; i++) {
            subtrees[i] = -1;
            adj[i].clear();
        }
        bool impossible = false;
        for (int i = 0; i < M; i++) {
            if (usingNode[X[i]] && usingNode[Y[i]] && usingNode[Z[i]]) {
                if ((X[i] == root || Y[i] == root) && Z[i] != root) {
                    // Impossible
                    impossible = true;
                    break;
                } else if (Z[i] != root) {
                    // Add to adjacency list
                    adj[X[i]].push_back(Z[i]);
                    adj[Z[i]].push_back(X[i]);
                    adj[Y[i]].push_back(Z[i]);
                    adj[Z[i]].push_back(Y[i]);
                }
            }
        }
        if (impossible) continue;

        // Floodfill
        // cout << "root " << root+1 << ": ";
        int currST = 0;
        for (int i = 0; i < N; i++) {
            if (usingNode[i] && subtrees[i] == -1 && i != root) {
                floodfill(i, currST++, subtrees);
            }
            // cout << subtrees[i] << ' ';
        }
        // cout << endl;

        // Make sure LCA conditions are satisfied
        for (int i = 0; i < M; i++) {
            if (usingNode[X[i]] && usingNode[Y[i]] && Z[i] == root) {
                if (subtrees[X[i]] == subtrees[Y[i]]) {
                    impossible = true;
                    break;
                }
            }
        }
        if (impossible) continue;
        
        // All subtrees work; fill in parent and recurse
        parents[root] = parent;
        bool newUsingNode[MAXN];
        for (int i = 0; i < currST; i++) {
            for (int j = 0; j < N; j++) {
                newUsingNode[j] = (usingNode[j] && subtrees[j] == i && j != root);
            }
            genTree(root, newUsingNode);
        }
        return;
    }

    // No roots worked
    possible = false;
}

void solve(int tn) {
    fin >> N >> M;
    for (int i = 0; i < M; i++) {
        fin >> X[i] >> Y[i] >> Z[i];
        X[i]--;
        Y[i]--;
        Z[i]--;
    }
    possible = true;
    bool usingNode[MAXN];
    for (int i = 0; i < N; i++) usingNode[i] = true;
    genTree(-1, usingNode);

    fout << "Case #" << tn << ": ";
    if (possible) {
        for (int i = 0; i < N; i++) {
            if (i != 0) fout << " ";
            fout << parents[i] + 1;
        }
    } else fout << "Impossible";
    fout << endl;
}

int main() {
    int T; 
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}