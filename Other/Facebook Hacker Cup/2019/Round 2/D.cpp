#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 800005;
const ll INF = 1e12;

struct Object {
    int P, H;
    bool isClam;
    // Sort set by increasing hardness
    bool operator<(const Object& o) const {
        return H < o.H;
    }
};

struct State {
    int maxH;
    ll cost, zeroCost;
    // Sort by increasing maxH
    bool operator<(const State& o) const {
        return maxH < o.maxH;
    }
};

int N;
ll maxPLoc;
Object objects[MAXN];
set<Object> leftRocks, rightRocks;
set<State> states;
multiset<ll> zeroCosts;

void solve(int tn) {
    // cout << "Case " << tn << "\n";
    fin >> N;
    ll P[MAXN], H[MAXN];
    ll Ap, Bp, Cp, Dp, Ah, Bh, Ch, Dh;
    string str;
    fin >> P[0] >> P[1] >> Ap >> Bp >> Cp >> Dp >> H[0] >> H[1] >> Ah >> Bh >> Ch >> Dh >> str;
    for (int i = 2; i < N; i++) {
        P[i] = ((Ap * P[i-2] + Bp * P[i-1] + Cp) % Dp) + 1;
        H[i] = ((Ah * H[i-2] + Bh * H[i-1] + Ch) % Dh) + 1;
    }
    for (int i = 0; i < N; i++) {
        objects[i].P = P[i];
        objects[i].H = H[i];
        objects[i].isClam = (str[i] == 'C');
        if (objects[i].isClam) maxPLoc = max(P[i], maxPLoc);
    }
    // Sort in order of increasing position
    sort(objects, objects+N, [](const Object& o1, const Object& o2) {
        return o1.P < o2.P;
    });
    /*
    for (int i = 0; i < N; i++) {
        cout << objects[i].P << ' ' << objects[i].H << ' ' << objects[i].isClam << endl;
    }
    */

    states.insert({0, 0, INF});
    zeroCosts.insert(INF);
    Object currObj;
    int lastI = N;
    for (int i = 0; i < N; i++) {
        currObj = objects[i];
        if (currObj.isClam) {
            // Clam; merge all states that are smaller or equal
            State newState = {currObj.H, INF, INF};
            auto lowerState = states.upper_bound({currObj.H, -1, -1});
            lowerState--;
            while (true) {
                if (lowerState->cost < newState.cost) {
                    newState.cost = lowerState->cost;
                }
                zeroCosts.erase(zeroCosts.find(lowerState->zeroCost));
                states.erase(lowerState);
                if (states.empty()) break;
                lowerState = states.upper_bound({currObj.H, -1, -1});
                if (lowerState == states.begin()) break;
                lowerState--;
            }

            // Calculate new zero cost
            ll newZeroCost = newState.cost;
            auto higherRock = leftRocks.upper_bound(currObj);
            if (newZeroCost != INF && higherRock != leftRocks.end()) {
                newZeroCost += (currObj.P - higherRock->P) * 2;
                // Delta offset
                newZeroCost -= currObj.P * 2;
            } else newZeroCost = INF;
            newState.zeroCost = newZeroCost;

            states.insert(newState);
            zeroCosts.insert(newZeroCost);
            if (states.begin()->maxH != 0) {
                ll bestZeroCost = min((*zeroCosts.begin()) + currObj.P * 2, INF);
                states.insert({0, bestZeroCost, INF});
                zeroCosts.insert(INF);
            }
        } else {
            // Rock; zero all states with lower maxH sizes
            auto lowerState = states.lower_bound({currObj.H, -1, -1});
            lowerState--;
            while (lowerState->maxH != 0) {
                auto zeroState = states.begin();
                if (zeroState->cost > lowerState->cost) {
                    states.erase(zeroState);
                    states.insert({0, lowerState->cost, INF});
                }
                zeroCosts.erase(zeroCosts.find(lowerState->zeroCost));
                states.erase(lowerState);
                lowerState = states.lower_bound({currObj.H, -1, -1});
                lowerState--;
            }

            // Add rock to leftRocks
            while (!leftRocks.empty()) {
                auto lowerRock = leftRocks.begin();
                if (lowerRock->H <= currObj.H) {
                    // Old rock is useless
                    leftRocks.erase(lowerRock);
                } else break;
            }
            leftRocks.insert(currObj);
        }
        /*
        cout << "i = " << i << endl;
        cout << "States:\n";
        for (auto x : states) {
            cout << x.maxH << ' ' << x.cost << endl;
        }
        cout << "Zero costs:\n";
        for (auto x : zeroCosts) {
            cout << x << ' ';
        }
        cout << "\nRocks:\n";
        for (auto x : leftRocks) {
            cout << x.H << ' ' << x.P << endl;
        }
        */

        if (currObj.P == maxPLoc) {
            lastI = i+1;
            break;
        }
    }

    // Handle rocks on outer edges
    rightRocks.clear();
    for (int i = N-1; i >= lastI; i--) {
        while (!rightRocks.empty()) {
            auto lowerRock = rightRocks.begin();
            if (lowerRock->H <= objects[i].H) {
                // Old rock is useless
                rightRocks.erase(lowerRock);
            } else break;
        }
        rightRocks.insert(objects[i]);
    }
    ll answer = INF;
    for (auto state : states) {
        auto higherRock = rightRocks.upper_bound({-1, state.maxH, -1});
        if (higherRock != rightRocks.end()) {
            answer = min(state.cost + higherRock->P - maxPLoc, answer);
        }
        auto higherRock2 = leftRocks.upper_bound({-1, state.maxH, -1});
        if (higherRock2 != leftRocks.end()) {
            answer = min(state.cost + maxPLoc - higherRock2->P, answer);
        }
    }
    if (states.begin()->maxH == 0) {
        answer = min(states.begin()->cost, answer);
    }

    answer += maxPLoc;
    fout << "Case #" << tn << ": " << (answer >= INF ? -1 : answer) << endl;

    // Reset
    leftRocks.clear();
    zeroCosts.clear();
    states.clear();
    maxPLoc = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}