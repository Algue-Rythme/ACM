#include <algorithm>
#include <iostream>
#include <vector>

#define _DEBUG_

using namespace std;

int main() {
    unsigned int nbTests;
    cin >> nbTests;
    for (unsigned int test = 0; test < nbTests; ++test) {
        unsigned int nbObjects;
        cin >> nbObjects;

        vector<unsigned int> value(nbObjects);
        vector<unsigned int> weight(nbObjects);
        for (unsigned int object = 0; object < nbObjects; ++object) {
            cin >> value[object] >> weight[object];
        }

        const unsigned int maxWeight = 30 + 1;
        vector<vector<unsigned int>> dyna(maxWeight, vector<unsigned int>(2, 0));
        for (unsigned int object = 0; object < nbObjects; ++object) {
            bool even = object%2;
            bool odd = (object+1)%2;
            for (unsigned int p = 0; p < maxWeight; ++p) {
                dyna[p][even] = dyna[p][odd];
                if (p >= 1)
                    dyna[p][even] = max(dyna[p][even], dyna[p-1][even]);
                if (weight[object] <= p) {
                    dyna[p][even] = max(dyna[p][even], dyna[p - weight[object]][odd] + value[object]);
                }
            }
        }

        unsigned int totalValue = 0;
        unsigned int nbPersons;
        cin >> nbPersons;
        for (unsigned int person = 0; person < nbPersons; ++person) {
            unsigned int bring;
            cin >> bring;
            totalValue += dyna[bring][(nbObjects+1)%2];
        }

        cout << totalValue << "\n";
    }
}
