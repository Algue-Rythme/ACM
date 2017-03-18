#include <algorithm>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

using namespace std;

int64_t pgcd(int64_t a, int64_t b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    while (a % b != 0) {
        int64_t t = (a%b + b)%b;
        a = b;
        b = t;
    }
    return b;
}

int64_t pgcd_vect(const vector<int64_t>& vect) {
    int64_t best = vect[0];
    for_each(begin(vect)+1, end(vect), [&](int64_t other){
        best = pgcd(best, other);
    });
    return (best != 0) ? best : -vect[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int nbTestsCase;
    cin >> nbTestsCase;
    for (unsigned int test = 0; test < nbTestsCase; ++test) {
        unsigned int nbSerials;
        cin >> nbSerials;
        vector<int64_t> serials(nbSerials, 0);
        vector<int64_t> a10;
        for (auto& serial : serials) {
            int64_t a;
            for (unsigned int i = 0; i < 9; ++i) {
                cin >> a;
                serial += a;
            }
            cin >> a;
            if (serial > a)
                serial -= a;
            else
                serial = a - serial;
            a10.push_back(a);

        }

        int64_t s = pgcd_vect(serials);
        if (s == 1 || *max_element(begin(a10), end(a10)) >= s)
            cout << "impossible\n";
        else
            cout << s << "\n";
    }
}
