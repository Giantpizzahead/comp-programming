/*
https://www.facebook.com/codingcompetitions/hacker-cup/2014/qualification-round/problems/B

This is just implementation... I don't think there's a "pattern" to follow for the second part.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

class Person {
private:
    string name;
    int shotPct, height;
public:
    Person(string name, int shotPct, int height) : name(name), shotPct(shotPct), height(height) {

    };

    bool operator<(const Person& other) const {
        return make_tuple(shotPct, height) < make_tuple(other.shotPct, other.height);
    }

    string getName() {
        return name;
    }
};

// Returns the names of the active team members after M minutes.
vector<string> genFinalActive(int teamSize, int M, int P, vector<string>& names) {
    assert(teamSize >= P);
    vector<bool> isActive(teamSize);
    rep(i, 0, P) isActive[i] = true;
    vector<int> timePlayed(teamSize);

    int bestTime;
    rep(t, 0, M) {
        if (teamSize == P) continue;  // No switching

        // Update playtime
        rep(i, 0, teamSize) if (isActive[i]) timePlayed[i]++;
        // Person to switch out
        int switchOut = -1;
        bestTime = -1;
        for (int i = teamSize-1; i >= 0; i--) if (isActive[i] && timePlayed[i] > bestTime) {
            switchOut = i, bestTime = timePlayed[i];
        }
        // Person to switch in
        int switchIn = -1;
        bestTime = M+1;
        rep(i, 0, teamSize) if (!isActive[i] && timePlayed[i] < bestTime) {
            switchIn = i, bestTime = timePlayed[i];
        }
        // Perform switch
        isActive[switchOut] = false;
        isActive[switchIn] = true;
    }

    vector<string> activeNames;
    rep(i, 0, teamSize) if (isActive[i]) activeNames.push_back(names[i]);
    return activeNames;
}

void solve() {
    int N, M, P; cin >> N >> M >> P;
    vector<Person> people;

    // Generate draft names
    rep(i, 0, N) {
        string name; int shotPct, height;
        cin >> name >> shotPct >> height;
        people.push_back(Person(name, shotPct, height));
    }
    sort(all(people));
    reverse(all(people));
    // rep(i, 0, N) cout << people[i].getName() << "\n";

    // Determine team rotations (same for both teams)
    vector<string> team1, team2;
    rep(i, 0, N) (i % 2 == 0 ? team1 : team2).push_back(people[i].getName());
    vector<string> active1 = genFinalActive((N+1)/2, M, P, team1);
    vector<string> active2 = genFinalActive(N/2, M, P, team2);

    // Output names
    for (string& name : active2) active1.push_back(name);
    sort(all(active1));
    for (string& name : active1) cout << " " << name;
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("basketball_game_input.txt", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 1, T+1) {
        cout << "Case #" << i << ":";
        solve();
    }
    return 0;
}
