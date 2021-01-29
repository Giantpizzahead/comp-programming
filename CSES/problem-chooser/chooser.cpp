#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <time.h>

using namespace std;

ifstream fin("problem-chooser/problems.txt");

int N;
string quotes[] {"You can do it!", "Good luck!", "Let's do this!", "Finish this thing!", "Get that AC!", "Happy solving!"};
string success[] {"Congrats!", "I knew you could do it <3", "Nice job!", "GG!", "Not bad!", "Awesome!", "Wow!", "Another problem down!", "ACs for days ;)", "Impressive!"};

struct Problem {
    int solved, numSolved, numUnsolved;
    string name;
};

Problem problems[100005];
vector<int> unsolvedIndexes;

int main() {
    fin >> N;
    int s;
    string n;
    for (int i = 0; i < N; i++) {
        fin >> s;
        fin.get();
        getline(fin, n);
        problems[i].solved = s;
        problems[i].name = n;
        if (s == 0) unsolvedIndexes.push_back(i);
    }
    int ns, nu;
    for (int i = 0; i < N; i++) {
        fin >> ns >> nu;
        problems[i].numSolved = ns;
        problems[i].numUnsolved = nu;
    }
    srand(time(NULL));

    cout << string(80, '-') << endl;
    cout << "# solved: " << N - unsolvedIndexes.size() << endl;
    cout << "# remaining: " << unsolvedIndexes.size() << endl << endl;

    choiceSelect:
    string choice;
    cout << "Would you like to (g)et a new problem or (m)ark a problem as solved? ";
    cin >> choice;
    locale loc;
    choice[0] = tolower(choice[0]);
    cin.get();
    if (choice[0] != 'g' && choice[0] != 'm') {
        cout << "Invalid choice!\n" << endl;
        goto choiceSelect;
    }

    if (choice[0] == 'g') {
        // New problem
        int nextIndex = unsolvedIndexes[rand() % unsolvedIndexes.size()];
        Problem& nextProblem = problems[nextIndex];
        cout << "\nNext problem: " << nextProblem.name << " (Problem #" << nextIndex+1 << ", " << nextProblem.numSolved << "/" << nextProblem.numUnsolved << ")" << endl;
        cout << quotes[rand() % (sizeof(quotes) / sizeof(*quotes))] << endl;
    } else if (choice[0] == 'm') {
        // Mark problem as solved
        problemSelect:
        cout << "Type the name of the problem you solved: ";
        getline(cin, choice);

        // Find problem
        int chosenI = -1;
        vector<int> foundLocs;
        for (int i = 0; i < N; i++) {
            if (problems[i].name == choice) {
                foundLocs.push_back(i);
                
            }
        }
        if (foundLocs.empty()) {
            cout << "Invalid problem name!\n" << endl;
            goto problemSelect;
        }

        if (foundLocs.size() == 1) chosenI = foundLocs.front();
        else {
            cout << "Which problem # (";
            for (int i = 0; i < foundLocs.size(); i++) {
                cout << foundLocs[i]+1 << (i == foundLocs.size()-1 ? ")? " : ", ");
            }
            getline(cin, n);
            for (int x : foundLocs) {
                if (n == to_string(x+1)) {
                    chosenI = x;
                    break;
                }
            }
            if (chosenI == -1) {
                cout << "Invalid problem #!\n" << endl;
                goto problemSelect;
            }
        }

        if (problems[chosenI].solved == 1) {
            cout << "Problem already solved!\n" << endl;
            goto problemSelect;
        }
        problems[chosenI].solved = 1;
        cout << "\nProblem " << choice << " solved!" << endl;
        cout << success[rand() % (sizeof(success) / sizeof(*success))] << endl;

        // Update problems.txt
        ofstream fout("problem-chooser/problems.txt");
        fout << N << endl;
        for (int i = 0; i < N; i++) {
            fout << problems[i].solved << " " << problems[i].name << endl;
        }
        for (int i = 0; i < N; i++) {
            fout << problems[i].numSolved << " " << problems[i].numUnsolved << endl;
        }
    }
    
    cout << string(80, '-') << endl;
}