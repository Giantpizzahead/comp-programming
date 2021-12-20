#include <iostream>
#include <algorithm>
#include <queue>

#define MAXN 100001
#define INF 1000000007

using namespace std;

struct Stop {
    int dist, amount;
    Stop() : dist(-INF), amount(-INF) {}
    Stop(int dist, int amount) : dist(dist), amount(amount) {}
};

bool compStops(const Stop& a, const Stop& b) {
    return (a.dist > b.dist);
}

int N;
Stop stops[MAXN];

int main() {
    cin >> N;
    int dist, amount;
    for (int i = 0; i < N; i++) {
        cin >> dist;
        cin >> amount;
        stops[i] = {dist, amount};
    }
    stops[N] = {0, 0};

    sort(begin(stops), end(stops), compStops);
    priority_queue<int> allowedPetrol;

    int distLeft, patrolLeft, numStops = 0;
    cin >> distLeft;
    cin >> patrolLeft;
    for (int i = 0; i <= N; i++) {
        patrolLeft -= (distLeft - stops[i].dist);
        distLeft = stops[i].dist;

        // cout << stops[i].dist << " " << stops[i].amount << endl;
        // cout << "Patrol left: " << patrolLeft << endl;

        // Must refuel at a petrol station
        while (!allowedPetrol.empty() && patrolLeft < 0) {
            patrolLeft += allowedPetrol.top();
            allowedPetrol.pop();
            numStops++;
        }
        if (patrolLeft < 0) {
            // Impossible
            cout << -1 << endl;
            exit(0);
        }

        allowedPetrol.emplace(stops[i].amount);
    }

    cout << numStops << endl;
}