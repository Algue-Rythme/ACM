#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    const uint64_t maxPennies = 30*1000 + 1;
    vector<uint64_t> dyna(maxPennies, 0);
    vector<uint64_t> coins = {1, 5, 10, 25, 50};

    dyna[0] = 1;
    for (uint64_t coin : coins) {
        for (uint64_t penny = 0; penny <= maxPennies; ++penny) {
            if (penny >= coin) {
                dyna[penny] += dyna[penny - coin];
            }
        }
    }

    uint64_t nbPennies;
    while (cin >> nbPennies) {
        uint64_t answer = dyna[nbPennies];
        if (answer == 1)
            cout << "There is only 1 way to produce " << nbPennies << " cents change.\n";
        else
            cout << "There are " << answer << " ways to produce " << nbPennies << " cents change.\n";
    }
}
