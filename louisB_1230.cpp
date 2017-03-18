#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

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
        uint64_t x, y, n;
        if (cin >> x >> y >> n)
            cout << power_mod(x % n, y, n) << "\n";
        else
            break ;
    }
}
