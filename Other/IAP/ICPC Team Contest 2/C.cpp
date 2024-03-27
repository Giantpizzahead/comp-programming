#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
vector<pair<int, vector<int>>> v;
map<int, vector<pair<int, int>>> ans;
int n,m,q,par[1000001];
map<int, int> mn;
vector<int> fl;

int find(int curr){
    return curr == par[curr] ? curr : par[curr] = find(par[curr]);
}

void getans(vector<pair<int, int>> v2){
    for(auto i : v2){
        if(i.second <= n){
            fl.push_back(i.second);
        }else{
            getans(ans[i.second]);
        }
    }
}

void solve() {
    cin >> n >> m >> q;
    for(int i = 0 ; i < m ; i += 1){
        int a, b;
        cin >> a >> b;
        vector<int> c;
        for(int j = 0 ; j < b ; j += 1){
            int d;
            cin >> d;
            c.push_back(d);
        }
        v.push_back({a, c});
    }
    vector<int> p;
    for(int i = 1 ; i <= n ; i += 1){
        p.push_back(i);
    }
    v.push_back({-1, p});
    m += 1;
    for(int i = 1 ; i <= n ; i += 1){
        par[i] = i;
        mn[i] = i;
    }
    sort(v.rbegin(), v.rend());
    int cnt = n+1;
    for(auto i : v){
        set<int> st;
        for(auto j : i.second){
            st.insert(find(j));
        }
        vector<int> v2;
        int mn2 = 1000000;
        for(auto j : st){
            ans[cnt].push_back({mn[j], j});
            mn2 = min(mn2, mn[j]);
            par[j] = cnt;
        }
        sort(ans[cnt].begin(), ans[cnt].end());
        mn[cnt] = mn2;
        par[cnt] = cnt;
        cnt += 1;
    }
    // for(int i = n+1 ; i <= n+m ; i += 1){
    //     for(auto j : ans[i]){
    //         cout << j.first << " " << j.second << "   ";
    //     }cout << endl;
    // }
    getans(ans[cnt-1]);
    // for(auto i : fl){
    //     cout << i << " ";
    // }cout << endl;
    map<int, int> qs;
    cnt = 0;
    for(auto i : fl){
        cnt += 1;
        qs[cnt] = i;
    }
    for(int i = 0 ; i < q ; i += 1){
        int a;
        cin >> a;
        cout << qs[a] << endl;
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
