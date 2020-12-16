#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
const int MAXN = 305;
const ll INF = 2e18 + 10;

struct Node {
    Node* kids[26];
    int id = 0, v = 0, totalV = -1, pe;
    Node* p = nullptr;
    Node* suf = nullptr;
    Node* dict = nullptr;

    Node(int id, Node* p, int pe) : id(id), pe(pe), p(p) {
        for (int i = 0; i < 26; i++) kids[i] = nullptr;
    }
};

vector<Node*> nodes;

void insert(Node* n, string& str, int i, int v) {
    if (i == str.length()) {
        n->v += v;
        return;
    }
    int x = str[i] - 'a';
    if (!n->kids[x]) {
        nodes.push_back(new Node(nodes.size(), n, x));
        n->kids[x] = *nodes.rbegin();
    }
    insert(n->kids[x], str, i+1, v);
}

Node* genSuf(Node* n) {
    if (n->suf) return n->suf;
    n->suf = genSuf(n->p);
    while (n->suf->id != 0 && !n->suf->kids[n->pe]) {
        n->suf = genSuf(n->suf);
    }
    if (n->suf != n->p && n->suf->kids[n->pe]) n->suf = n->suf->kids[n->pe];
    for (int i = 0; i < 26; i++) {
        if (n->kids[i]) genSuf(n->kids[i]);
    }
    return n->suf;
}

int genValue(Node* n) {
    if (n->totalV != -1) return n->totalV;
    n->totalV = n->v + genValue(n->suf);
    for (int i = 0; i < 26; i++) {
        if (n->kids[i]) genValue(n->kids[i]);
    }
    return n->totalV;
}

void print(Node* n, int indent = 0) {
    cout << "(" << n->id << " " << n->totalV << ") ";
    for (int i = 0; i < 26; i++) {
        if (n->kids[i]) {
            cout << (char) ('a' + i) << ' ';
            print(n->kids[i], indent+1);
        }
    }
    cout << "< ";
    if (!indent) cout << endl;
}

Node* trie;
int N, M;
ll L;
int A[MAXN];

ll base[1][MAXN], mat[MAXN][MAXN], newMat[MAXN][MAXN];

void doubleMat() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            newMat[i][j] = -INF;
            for (int k = 0; k < M; k++) {
                newMat[i][j] = max(mat[i][k] + mat[k][j], newMat[i][j]);
            }
        }
    }
    swap(newMat, mat);
}

ll temp[MAXN][MAXN];
void joinMatrices(ll A[][MAXN], ll B[][MAXN], int X) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < M; j++) {
            temp[i][j] = -INF;
            for (int k = 0; k < M; k++) {
                temp[i][j] = max(A[i][k] + B[k][j], temp[i][j]);
            }
        }
    }
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = temp[i][j];
        }
    }
}

void calcBase() {
    for (int i = 0; i < M; i++) {
        base[0][i] = -INF;
    }
    base[0][0] = 0;
    while (L > 0) {
        // for (int i = 0; i < M; i++) {
        //     for (int j = 0; j < M; j++) cout << mat[i][j] << " ";
        //     cout << endl;
        // }
        // cout << endl;
        if (L % 2 == 1) {
            joinMatrices(base, mat, 1);
        }
        L /= 2;
        joinMatrices(mat, mat, M);
        // doubleMat();
    }
}

int main() {
    nodes.push_back(new Node(nodes.size(), nullptr, -1));
    trie = *nodes.rbegin();
    cin >> N >> L;
    for (int i = 0; i < N; i++) cin >> A[i];
    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        insert(trie, str, 0, A[i]);
    }
    M = nodes.size();
    trie->suf = trie;
    trie->totalV = 0;
    for (int i = 0; i < 26; i++) {
        if (trie->kids[i]) genSuf(trie->kids[i]);
    }
    for (int i = 0; i < 26; i++) {
        if (trie->kids[i]) genValue(trie->kids[i]);
    }
    // print(trie);

    // Gen transition matrix
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) mat[i][j] = -INF;
        for (int j = 0; j < 26; j++) {
            // Add this character to end
            Node* n = nodes[i];
            while (n->id != 0 && !n->kids[j]) {
                n = n->suf;
            }
            if (n->kids[j]) n = n->kids[j];
            mat[i][n->id] = n->totalV;
        }
    }

    calcBase();
    ll answer = 0;
    for (int i = 0; i < M; i++) {
        // cout << base[0][i] << " ";
        answer = max(base[0][i], answer);
    }
    // cout << endl;
    cout << answer << endl;
}