// 5537376230390876637302048746832985971773659831892672

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;

struct BigInteger {
    string S;

    BigInteger(string str) {
        S = str;
    }

    BigInteger& operator+=(const BigInteger& o) {
        const string& T = o.S;
        int carry = 0;
        string U = "";
        for (int i = 0; i < sz(S) || i < sz(T) || carry != 0; i++) {
            int a = (i < sz(S) ? S[sz(S)-1-i]-'0' : 0);
            int b = (i < sz(T) ? T[sz(T)-1-i]-'0' : 0);
            int c = a+b+carry;
            if (c >= 10) {
                carry = 1;
                c -= 10;
            } else carry = 0;
            U += static_cast<char>('0' + c);
        }
        reverse(all(U));
        S = U;
        return *this;
    }

    friend BigInteger operator+(BigInteger a, const BigInteger& b) {
        a += b;
        return a;
    }
};

std::ostream& operator<<(std::ostream& os, const BigInteger& obj)
{
    os << obj.S;
    return os;
}

void solve() {
    BigInteger curr("0");
    cin >> N;
    string str;
    rep(i, 0, N) {
        cin >> str;
        curr += BigInteger(str);
    }
    cout << curr << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}