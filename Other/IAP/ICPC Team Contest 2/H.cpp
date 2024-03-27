#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int N = 1 << 24;
const ll INF = 1e18;
#define RANGE 5

vector<pair <int, int>> get_offsets(string s) {
    int n = s.size();
    int x = 0, y = 0;
    vector <pair <int,int>> v;
    v.push_back({0, 0});
    for(int i = 0; i < n; i++) {
        if(s[i] == 'E') x += 1;
        if(s[i] == 'W') x -= 1;
        if(s[i] == 'N') y += 1;
        if(s[i] == 'S') y -= 1;
        v.push_back({x, y});
    }
    return v;
}

pair <int, int> add_pairs(pair <int, int> a, pair <int, int> b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

ll get_collide_time(pair <int, int> pos1, string s1, pair <int, int> pos2, string s2) {
    vector<pair<int,int>> v1 = get_offsets(s1);
    vector<pair<int,int>> v2 = get_offsets(s2);
    int n = v1.size();
    auto o1 = v1.back();
    auto o2 = v2.back();
    ll opt = INF;
    int moves = s1.size();
    for(int i = 0; i < n; i++) {
        pair <int, int> d1 = add_pairs(pos1, v1[i]);
        pair <int, int> d2 = add_pairs(pos2, v2[i]);
        // cout << d1.first << " " << d1.second << endl;
        // cout << d2.first << " " << d2.second << endl;
        // d1.first + t * o1.first == d2.first + t * o2.first
        // d1.second + t * o1.second == d2.second + t * o2.second
        ll t = 0;
        if(o1.first != o2.first) {
            t = (d2.first - d1.first) / (o1.first - o2.first); 
        }
        if(o1.second != o2.second) {
            t = (d2.second - d1.second) / (o1.second - o2.second);
        }
        if(d1.first + t * o1.first == d2.first + t * o2.first &&
           d1.second + t * o1.second == d2.second + t * o2.second && t >= 0) {
            opt = min(opt, t * moves + i);
        }
    }
    return opt;
}

ll get_fall_time(pair <int, int> pos, string s) {
    int moves = s.size();
    vector<pair <int, int>> v = get_offsets(s);
    int n = v.size();
    pair <int, int> d = v.back();
    ll opt = INF;
    for(int i = 0; i < n; i++) {
        pair <int, int> o = add_pairs(pos, v[i]);
        if(o.first < 0 || o.first >= N) {
            opt = min(opt, (ll) i);
            continue;
        }
        if(o.second < 0 || o.second >= N) {
            opt = min(opt, (ll) i);
            continue;
        }
        // o.first + t * d.first <= -1
        if(d.first < 0) {
            ll t = (-1 - o.first) / d.first;
            t += RANGE;
            while(o.first + t * d.first < 0) t -= 1;
            t += 1;
            opt = min(opt, t * moves + i);
        }

        // o.first + t * d.first >= N
        if(d.first > 0) {
            ll t = (N - o.first) / d.first;
            t += RANGE;
            while(o.first + t * d.first >= N) t -= 1;
            t += 1;
            opt = min(opt, t * moves + i);
        }
        
        // o.second + t * d.second <= -1
        if(d.second < 0) {
            ll t = (-1 - o.second) / d.second;
            t += RANGE;
            while(o.second + t * d.second < 0) t -= 1;
            t += 1;
            opt = min(opt, t * moves + i);
        }
        // o.second + t * d.second >= N
        if(d.second > 0) {
            ll t = (N - o.second) / d.second;
            t += RANGE;
            while(o.second + t * d.second >= N) t -= 1;
            t += 1;
            opt = min(opt, t * moves + i);
        }
    }
    return opt;
}

void solve() {
    pair <int, int> pos1, pos2;
    string s1, s2;
    cin >> pos1.first >> pos1.second;
    cin >> pos2.first >> pos2.second;
    int n;
    cin >> n;
    cin >> s1;
    cin >> s2;
    ll t = get_collide_time(pos1, s1, pos2, s2);
    ll f1 = get_fall_time(pos1, s1);
    ll f2 = get_fall_time(pos2, s2);
    if(min(f1, f2) > t) {
        cout << "The two robots collide at time " << t << "." << endl;
    } else if (f1 == f2) {
        cout << "Both robots fall off the board at time " << f1 << "." << endl; 
    } else if (f1 < f2) {
        cout << "Robot 1 falls off the board at time " << f1 << "." << endl;
    } else {
        cout << "Robot 2 falls off the board at time " << f2 << "." << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
