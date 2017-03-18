#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const uint64_t MODULO_V = 1000*1000*1000+7;

uint64_t power_mod(uint64_t x, uint64_t y, uint64_t n) {
    uint64_t b = x;
    uint64_t r = 1;
    while (y != 0) {
        if (y & 1)
            r *= b;
        r %= n;

        b = b*b;
        b %= n;

        y >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int nbTests;
    cin >> nbTests;
    for (unsigned int test = 0; test < nbTests; ++test) {
        unsigned int nbPrimesFactors;
        cin >> nbPrimesFactors;
        vector<uint64_t> primes(nbPrimesFactors);
        vector<uint64_t> mult(nbPrimesFactors);
        for (unsigned int factor = 0; factor < nbPrimesFactors; ++factor) {
            cin >> primes[factor] >> mult[factor];
        }

        uint64_t sum = 0;

        // TODO

        cout << "Case " << test+1 << ": " << sum << "\n";
    }
}
