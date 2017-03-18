#include <algorithm>
#include <iostream>
#include <vector>

#define _DEBUG_

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    const size_t maxSize = 1000 + 1;
    string word1, word2;
    while (getline(cin, word1) && getline(cin, word2)) {
        vector<vector<unsigned int>> dyna(maxSize, vector<unsigned int>(maxSize, 0));
        for (unsigned int i = 0; i < word1.size(); ++i) {
            for (unsigned int j = 0; j < word2.size(); ++j) {
                if (word1[i] == word2[j]) {
                    dyna[i][j] = 1;
                    if (i > 0 && j > 0)
                        dyna[i][j] += dyna[i-1][j-1];
                } else {
                    int left = (i > 0) ? dyna[i-1][j] : 0;
                    int right = (j > 0) ? dyna[i][j-1] : 0;
                    dyna[i][j] = max(left, right);
                }

                #ifdef DEBUG
                cout << dyna[i][j] << " ";
                #endif
            }
            #ifdef DEBUG
            cout << "\n";
            #endif
        }
        if (word1.size() == 0 || word2.size() == 0)
            cout << "0\n";
        else
            cout << dyna[word1.size()-1][word2.size()-1] << "\n";
    }
}
