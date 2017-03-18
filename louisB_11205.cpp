#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

unsigned int countBit(unsigned int v) {
    unsigned int count = 0;
    while (v != 0) {
        count += (v&1);
        v >>= 1;
    }
    return count;
}

int main() {
    unsigned int nbProblems;
    scanf("%u", &nbProblems);
    for (unsigned int problem = 0; problem < nbProblems; ++problem) {
        unsigned int nbBits, nbSymbols;
        scanf("%u%u",&nbBits, &nbSymbols);
        vector<unsigned int> symbols(nbSymbols);
        for (unsigned int symbol = 0; symbol < nbSymbols; ++symbol) {
            unsigned int v = 0;
            for (unsigned int bit = 0; bit < nbBits; ++bit) {
                unsigned int vBit = 0;
                scanf("%u", &vBit);
                v <<= 1;
                v |= vBit;
            }
            symbols[symbol] = v;
        }

        unsigned int vSelect = 0;
        unsigned int countSelect = nbBits + 1;
        for (unsigned int select = 0; select < (1 << nbBits); ++select) {
            vector<bool> seen(1 << nbBits, false);
            bool candidate = true;
            for (unsigned int symbol : symbols) {
                if (seen[symbol & select]) {
                    candidate = false;
                    break ;
                }
                seen[symbol & select] = true;
            }
            if (candidate) {
                unsigned int count = countBit(select);
                if (count < countSelect) {
                    vSelect = select;
                    countSelect = count;
                }
            }
        }

        printf("%u\n", countSelect);
    }
}
