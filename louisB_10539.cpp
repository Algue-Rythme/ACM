#include <algorithm>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

using namespace std;

const uint64_t primesMax = 1000*1000;
vector<bool> isPrime(primesMax+1, true);
vector<uint64_t> primeList;

void crible() {
    for (uint64_t i = 2; i <= primesMax; ++i) {
        if (!isPrime[i])
            continue ;
        primeList.push_back(i);
        for (uint64_t j = i*2; j <= primesMax; j += i) {
            isPrime[j] = false;
        }
    }
}

uint64_t answer(uint64_t low, uint64_t high) {
    uint64_t count = 0;
    for (const auto& prime : primeList) {
        if (prime > high)
            break ;
        uint64_t p = prime*prime;
        while (p <= high) {
            if (p >= low)
                ++count;
            p *= prime;
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    crible();

    uint64_t nbTests;
    cin >> nbTests;
    for (uint64_t test = 0; test < nbTests; ++test) {
        uint64_t low, high;
        cin >> low >> high;
        cout << answer(low, high) << "\n";
    }
}
