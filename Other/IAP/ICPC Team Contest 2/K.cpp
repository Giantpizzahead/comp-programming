#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int long long

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
vector<int> a(4,0);
int x, y, z;

int gcd(int p, int q){
    if(p > q){
        swap(p, q);
    }
    if(p == 0){
        return q;
    }
    return gcd(q%p, p);
}

int mv(int c , int d){
    if(a[c] <= a[d]){
        cout << c << " " << d << endl;
    }else{
        cout << d << " " << c << endl;
    }
    if(a[c] >= a[d]){
        a[c] -= a[d];
        a[d] = 2*a[d];
    }else{
        a[d] -= a[c];
        a[c] = 2*a[c];
    }
    if(a[1] == max({a[1], a[2], a[3]})){
        z = 1;
        if(a[2] == min({a[2], a[3]})){
            x = 2, y = 3;
        }else{
            x = 3, y = 2;
        }
    }else if(a[2] == max({a[1], a[2], a[3]})){
        z = 2;
        if(a[1] == min({a[1], a[3]})){
            x = 1, y = 3;
        }else{
            x = 3, y = 1;
        }
    }else{
        z = 3;
        if(a[1] == min({a[1], a[2]})){
            x = 1, y = 2;
        }else{
            x = 2, y = 1;
        }
    }
    // cout << a[1] << " " << a[2] << " " << a[3] << endl;
    if(min({a[1], a[2], a[3]}) == 0){
        cout << "0 0" << endl;
        return 1;
    }
    if(a[1] == a[2]){
        cout << 1 << " " << 2 << endl;
        cout << "0 0" << endl;
        return 1;
    }
    if(a[2] == a[3]){
        cout << 2 << " " << 3 << endl;
        cout << "0 0" << endl;
        return 1;
    }
    if(a[1] == a[3]){
        cout << 1 << " " << 3 << endl;
        cout << "0 0" << endl;
        return 1;
    }
    return 0;
}

bool pw(int r){
    while(r != 1){
        if(r%2 == 1){
            return false;
        }
        r /= 2;
    }
    return true;
}

void solve(int l, int ll, int lll) {
    a[1] = l, a[2] = ll, a[3] = lll;
    // cin >> a[1] >> a[2] >> a[3];
    if(mv(1, 2)){
        return ;
    }
    while(true){
        int p = x, q = y, s = z, g = gcd(a[x], a[y]);
        while(gcd(a[p], a[q]) != a[p]){
            if(mv(p, q)){
                return ;
            }
        }
        if(x == p && y == q){
            while(!pw((a[p]+a[q])/g)){
                while(a[p] != g){
                    if(mv(p, q)){
                        return ;
                    }
                }
                mv(p, s);
                g = gcd(a[p], a[q]);
            }
            while(!mv(p, q)){
                continue;
            }
            return;
        }
        while(a[q] > a[s]){
            if(mv(q, s)){
                return ;
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    for(int i = 1 ; i <= 100 ; i += 1){
        for(int j = 1 ; j <= 100 ; j += 1){
            for(int k = 1 ; k <= 100 ; k += 1){
                // cout << i << " " << j << " " << k << endl;
                solve(i, j, k);
            }
        }
    }
    // int T = 1;
    // rep(i, 0, T) solve();
    return 0;
}
