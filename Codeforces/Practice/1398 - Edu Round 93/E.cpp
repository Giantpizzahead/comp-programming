#include <iostream>
#include <set>

using namespace std;
using ll = long long;

struct Spell {
    int tp, d;

    // Sort by decreasing power
    bool operator<(const Spell& o) const {
        return o.d < d;
    }
};

int N;
set<Spell> lightningSpells, fireSpells, noDouble, yesDouble;

void solve() {
    cin >> N;
    int numLightning = 0, numFire = 0, lowestSpell = 0;
    ll doubleSum = 0, totalSum = 0;
    int tp, d;
    for (int i = 0; i < N; i++) {
        cin >> tp >> d;
        if (d < 0) {
            // Removing spell
            d = -d;
            totalSum -= d;
            if (tp == 0) {
                fireSpells.erase({tp, d});
                numFire--;
                if (yesDouble.find({tp, d}) != yesDouble.end()) {
                    // Must replace this spell with another one to double
                    yesDouble.erase({tp, d});
                    doubleSum -= d;
                    Spell sp = *noDouble.begin();
                    noDouble.erase(sp);
                    yesDouble.insert(sp);
                    doubleSum += sp.d;
                }
                noDouble.erase({tp, d});
            } else {
                lightningSpells.erase({tp, d});
                numLightning--;
                // Must remove a spell from double
                if (yesDouble.find({tp, d}) == yesDouble.end()) {
                    Spell sp = *yesDouble.rbegin();
                    yesDouble.erase(sp);
                    noDouble.insert(sp);
                    doubleSum -= sp.d;
                } else {
                    yesDouble.erase({tp, d});
                    doubleSum -= d;
                }
                noDouble.erase({tp, d});
            }
        } else {
            // Adding spell
            noDouble.insert({tp, d});
            totalSum += d;
            if (tp == 0) {
                fireSpells.insert({tp, d});
                numFire++;
                // Add new spell to double if it's better than the others
                if (!yesDouble.empty()) {
                    Spell lowest = *yesDouble.rbegin();
                    if (lowest.d < d) {
                        yesDouble.erase(lowest);
                        noDouble.insert(lowest);
                        doubleSum -= lowest.d;
                        noDouble.erase({tp, d});
                        yesDouble.insert({tp, d});
                        doubleSum += d;
                    }
                }
            } else {
                lightningSpells.insert({tp, d});
                numLightning++;
                // Add new spell to double
                Spell sp = *noDouble.begin();
                noDouble.erase(sp);
                yesDouble.insert(sp);
                doubleSum += sp.d;
            }
        }

        // cout << "total: " << totalSum << " double: " << doubleSum << endl;

        if (numLightning == 0) {
            cout << totalSum << endl;
        } else if (numFire == 0) {
            // One lightning spell will be wasted
            cout << totalSum * 2 - (lightningSpells.rbegin()->d) << endl;
        } else {
            // Lightning spells can double some of the other spells
            // Take sum of spells with the highest power, minus weakest lightning spell (if included)
            if (yesDouble.find(*lightningSpells.rbegin()) != yesDouble.end()) {
                // Weakest lightning included; remove & replace
                ll newSum = totalSum + doubleSum - lightningSpells.rbegin()->d;
                if (!noDouble.empty()) {
                    newSum += noDouble.begin()->d;
                }
                cout << newSum << endl;
            } else cout << totalSum + doubleSum << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}