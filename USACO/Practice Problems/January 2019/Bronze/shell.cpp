#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	// Open shell.in to get input
	ifstream fin("shell.in");
	if (!fin) {
		cout << "what" << endl;
		return -1;
	}

	int N, a, b, g;
	fin >> N;

	int loc1 = 1, loc2 = 2, loc3 = 3;
	int ans1 = 0, ans2 = 0, ans3 = 0;
	for (int i = 0; i < N; i++) {
		fin >> a;
		fin >> b;
		fin >> g;

		// Swap the shells
		if (loc1 == a) loc1 = b;
		else if (loc1 == b) loc1 = a;
		if (loc2 == a) loc2 = b;
		else if (loc2 == b) loc2 = a;
		if (loc3 == a) loc3 = b;
		else if (loc3 == b) loc3 = a;

		// Add to answers
		if (g == loc1) ans1++;
		if (g == loc2) ans2++;
		if (g == loc3) ans3++;
	}
	fin.close();

	// Final answer is max # of points out of all 3
	// cout << ans1 << ' ' << ans2 << ' ' << ans3;
	int answer = max(max(ans1, ans2), ans3);

	// Output answer to shell.out
	ofstream fout("shell.out");
	fout << answer << endl;
	fout.close();

	return 0;
}