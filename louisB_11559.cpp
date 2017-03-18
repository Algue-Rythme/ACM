#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    uint64_t nbPeople, budget;
    uint64_t nbHotels, nbWeeks;
    while (cin >> nbPeople >> budget >> nbHotels >> nbWeeks) {
        uint64_t bestPrice = budget + 1;
        for (uint64_t hotel = 0; hotel < nbHotels; ++hotel) {
            uint64_t price;
            cin >> price;
            uint64_t cost = price*nbPeople;
            bool okay = false;
            for (uint64_t week = 0; week < nbWeeks; ++week) {
                uint64_t capacity;
                cin >> capacity;
                if (capacity >= nbPeople)
                    okay = true;
            }
            if (okay && cost < bestPrice)
                bestPrice = cost;
        }
        if (bestPrice <= budget)
            cout << bestPrice << "\n";
        else
            cout << "stay home\n";
    }
}
