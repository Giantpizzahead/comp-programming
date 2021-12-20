#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll N, K, divisorsN;
int Q, T;
vector<pair<ll, int>> factN, gcfK;

void factorizeN() {
    for (ll i = 2; i*i <= N; i++) {
        if (N % i == 0) {
            // This is a factor
            int cnt = 0;
            while (N % i == 0) {
                N /= i;
                cnt++;
            }
            factN.emplace_back(i, cnt);
        }
        if (N == 1) return;
    }
    // N is prime
    if (N != 1) factN.emplace_back(N, 1);
}

bool findGCFK() {
    gcfK.clear();
    for (auto p : factN) {
        int cnt = 0;
        while (K % p.first == 0 && cnt < p.second) {
            K /= p.first;
            cnt++;
        }
        gcfK.emplace_back(cnt, p.second - cnt);
    }
    return K == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    factorizeN();
    divisorsN = 1;
    for (auto p : factN) {
        divisorsN *= p.second + 1;
        // cout << p.first << ", " << p.second << endl;
    }
    for (int i = 0; i < Q; i++) {
        cin >> T >> K;
        bool divides = findGCFK();
        // for (auto p : gcfK) cout << p.first << ", " << p.second << endl;
        if (T == 1) {
            ll answer = 1;
            for (auto p : gcfK) {
                answer *= p.first + 1;
            }
            cout << answer << '\n';
        } else {
            ll answer = 1;
            if (!divides) answer = 0;
            else {
                for (auto p : gcfK) {
                    answer *= p.second + 1;
                }
            }
            if (T == 3) answer = divisorsN - answer;
            cout << answer << '\n';
        }
    }
    return 0;
}