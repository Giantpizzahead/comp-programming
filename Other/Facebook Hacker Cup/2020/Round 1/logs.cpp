#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 1000005;
const int MAXM = 1000005;

ll N, M, S;
ll drivers[MAXN], logs[MAXM];

bool check(ll seconds) {
    int logI = 0;
    for (int driverI = 0; driverI < N; driverI++) {
        int logStartI = logI;
        // Greedily plant charges in a range
        while (true) {
            // Time to plant charges & travel through all logs
            ll currTime = S * (logI - logStartI + 1);
            currTime += logs[logI] - logs[logStartI];
            // Time to get to the first log (always optimal to start on edge)
            currTime += min(abs(logs[logI] - drivers[driverI]), abs(logs[logStartI] - drivers[driverI]));
            if (currTime <= seconds) {
                // This works!
                logI++;
            } else {
                // Switch to next driver
                break;
            }
            if (logI == M) {
                // All logs used; check successful
                // cout << seconds << " true\n";
                return true;
            }
        }
    }
    // Not all charges were planted
    // cout << seconds << " false\n";
    return false;
}

void solve(int tn) {
    ll low = 0, high = 1e18;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    fout << "Case #" << tn << ": " << low << endl;
}

void parseInput(int tn) {
    ll K, Ap, Bp, Cp, Dp, Aq, Bq, Cq, Dq;
    fin >> N >> M >> K >> S;
    for (int i = 0; i < K; i++) {
        fin >> drivers[i];
    }
    fin >> Ap >> Bp >> Cp >> Dp;
    for (int i = 0; i < K; i++) {
        fin >> logs[i];
    }
    fin >> Aq >> Bq >> Cq >> Dq;
    for (int i = K; i < N; i++) {
        drivers[i] = (Ap * drivers[i-2] + Bp * drivers[i-1] + Cp) % Dp + 1;
    }
    for (int i = K; i < M; i++) {
        logs[i] = (Aq * logs[i-2] + Bq * logs[i-1] + Cq) % Dq + 1;
    }
    sort(drivers, drivers+N);
    sort(logs, logs+M);
    /*
    cout << "----" << endl;
    for (int i = 0; i < N; i++) cout << drivers[i] << " ";
    cout << endl;
    for (int i = 0; i < M; i++) cout << logs[i] << " ";
    cout << endl;
    */
    solve(tn);
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}