#include <iostream>
#include <string>
#include <vector>

std::string S, T;

int kmp(const std::string& S, const std::string& T) {
    // Create LCP array for the pattern
    std::vector<int> lcp(T.size());
    lcp[0] = -1;
    int currLCP = -1;
    for (int i = 1; i < T.size(); i++) {
        while (currLCP != -1 && T[i] != T[currLCP+1]) currLCP = lcp[currLCP];
        if (T[i] == T[currLCP+1]) currLCP++;
        lcp[i] = currLCP;
    }
    // for (int i = 0; i < T.size(); i++) std::cout << lcp[i] << (i+1 == T.size() ? "\n" : " ");

    // Find the pattern in the text
    int currPos = -1, answer = 0;
    for (int i = 0; i < S.size(); i++) {
        while (currPos != -1 && S[i] != T[currPos+1]) currPos = lcp[currPos];
        if (S[i] == T[currPos+1]) currPos++;
        if (currPos == T.size()-1) {
            // std::cout << "found starting at index " << i+1-T.size() << "\n";
            answer++;
            currPos = lcp[currPos];
        }
    }
    return answer;
}

int main() {
    std::cin >> S >> T;
    std::cout << kmp(S, T) << std::endl;
    return 0;
}