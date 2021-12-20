#include <iostream>
#include <string>
using namespace std;

int currCard = 0;
int deck[52];
int numLeft[12];

int drawCard() {
    return deck[currCard++];
}

void revealCard(int c) {
    numLeft[c]--;
}

struct Player {
    int cards[10];
    int numFilled = 0;
    bool smart = false;

    bool placeCard(int i) {
        int newCard = cards[i];
        cards[i] = -1;
        numFilled++;
        if (numFilled == 10) return true;
        return useCard(newCard);
    }

    bool useCard(int card) {
        revealCard(card);
        if (card == 11) return false;
        if (card == 10) {
            // Jack
            if (smart) {
                // Place in best spot (the one that would be the hardest to fill)
                int bestLoc = -1, minLeft = 5;
                for (int i = 0; i < 10; i++) {
                    if (cards[i] == -1) continue;
                    if (numLeft[i] < minLeft) {
                        bestLoc = i;
                        minLeft = numLeft[i];
                    }
                }
                return placeCard(bestLoc);
            } else {
                // Just place in first open
                for (int i = 0; i < 10; i++) {
                    if (cards[i] != -1) {
                        return placeCard(i);
                    }
                }
            }
        }
        if (cards[card] == -1) return false;  // Already filled
        else {
            // Place card here
            return placeCard(card);
        }
    }
};

Player player1, player2;

int main() {
    player1.smart = true;
    string str;
    cin >> str;
    for (int i = 0; i < 52; i++) {
        if (str[i] == 'A') deck[i] = 0;
        else if (str[i] == 'J') deck[i] = 10;
        else if (str[i] == 'Q' || str[i] == 'K') deck[i] = 11;
        else if (str[i] == 'T') deck[i] = 9;
        else deck[i] = str[i] - '1';
    }
    for (int i = 0; i < 52; i++) numLeft[deck[i]]++;
    // Deal initial cards
    for (int i = 0; i < 10; i++) player1.cards[i] = drawCard();
    for (int i = 0; i < 10; i++) player2.cards[i] = drawCard();
    bool turn1 = true;
    while (true) {
        int card = drawCard();
        if (turn1) {
            if (player1.useCard(card)) {
                cout << "Theta wins" << endl;
                break;
            }
        } else {
            if (player2.useCard(card)) {
                cout << "Theta loses" << endl;
                break;
            }
        }
        turn1 = !turn1;
    }
    return 0;
}