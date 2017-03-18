#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    unsigned int nbReviewers, nbPapers;
    while (cin >> nbReviewers >> nbPapers) {
        if (nbReviewers == 0 && nbPapers == 0)
            break;
        vector<string> provenance(nbPapers);
        vector<vector<unsigned int>> papers(nbPapers);
        vector<unsigned int> reviewersCount(nbPapers, 0);
        for (unsigned int paper = 0; paper < nbPapers; ++paper) {
            string name;
            cin >> name;
            provenance[paper] = name;
            for (unsigned int reviewer = 0; reviewer < nbReviewers; ++reviewer) {
                unsigned int num;
                cin >> num;
                papers[num-1].push_back(paper);
                reviewersCount[num-1] += 1;
            }
        }

        unsigned int countProblems = 0;
        for (unsigned int paper = 0; paper < nbPapers; ++paper) {
            if (reviewersCount[paper] != nbReviewers) {
                ++countProblems;
                continue ;
            }
            for (unsigned int reviewer = 0; reviewer < papers[paper].size(); ++reviewer) {
                if (count(begin(papers[paper]), end(papers[paper]), papers[paper][reviewer]) >= 2
                    || provenance[paper] == provenance[papers[paper][reviewer]]) {
                    ++countProblems;
                    break ;
                }
            }
        }

        if (countProblems == 0)
            cout << "NO PROBLEMS FOUND\n";
        else if (countProblems == 1)
            cout << "1 PROBLEM FOUND\n";
        else
            cout << countProblems << " PROBLEMS FOUND\n";
    }
}
