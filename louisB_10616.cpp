#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#define _DEBUG_

using namespace std;

const unsigned int nbNumbersMax = 200;
const unsigned int nbChoosenMax = 10;
const int64_t DMax = 20;
uint64_t dyna[nbNumbersMax+1][nbChoosenMax+1][DMax+1];
int64_t numbers[nbNumbersMax+1];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    unsigned int nbNumbers, nbQueries;
    unsigned int nbTests = 1;
    while (cin >> nbNumbers >> nbQueries) {
        if (nbNumbers == 0 && nbQueries == 0)
            return 0;

        cout << "SET " << nbTests << ":\n";
        nbTests += 1;

        for (unsigned int number = 0; number < nbNumbers; ++number) {
            cin >> numbers[number];
        }

        for (unsigned int query = 1; query <= nbQueries; ++query) {
            int64_t D;
            unsigned M;
            cin >> D >> M;

            for (unsigned int n = 0; n <= nbNumbers; ++n) {
                for (unsigned int m = 0; m <= nbChoosenMax; ++m) {
                    for (int64_t d = 0; d < DMax; ++d) {
                        dyna[n][m][d] = 0;
                    }
                }
            }

            for (unsigned int n = 0; n <= nbNumbers; ++n)
                dyna[n][0][0] = 1;

            for (unsigned int n = 1; n <= nbNumbers; ++n) {
                #ifdef DEBUG
                cout << "n = " << n << " | " << numbers[n-1] << "\n";
                #endif
                for (unsigned int m = 1; m <= min(M, n); ++m) {
                    #ifdef DEBUG
                    cout << "m = " << m << " | ";
                    #endif
                    for (int64_t d = 0; d < D; ++d) {

                        uint64_t dontTakeIt = dyna[n-1][m][d];

                        int64_t pred = D + d + (numbers[n-1]%D);
                        uint64_t takeIt = dyna[n-1][m-1][pred % D];

                        dyna[n][m][d] += (dontTakeIt + takeIt);

                        #ifdef DEBUG
                        cout << dyna[n][m][d] << " ";
                        #endif
                    }
                    #ifdef DEBUG
                    cout << "\n";
                    #endif
                }
            }

            uint64_t answer = dyna[nbNumbers][M][0];
            cout << "QUERY " << query << ": " << answer << "\n";
        }
    }
}
