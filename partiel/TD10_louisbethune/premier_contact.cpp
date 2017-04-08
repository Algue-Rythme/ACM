#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

inline uint64_t nextBase(uint64_t base) {
    if (base == 1)
        return 0;
    if (base == 0)
        return 2;
    return base + 1;
}

inline uint64_t get_digit(char digit) {
    if (digit >= '0' && digit <= '9')
        return digit - '0';
    return int(digit - 'a') + int(10);
}

inline bool is_good(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t nbTests;
    cin >> nbTests;
    //cin.ignore(1000, '\n');
    for (uint64_t test = 0; test < nbTests; ++test) {
        string line;
        cin >> line;
        //cout << line << endl;
        vector<uint64_t> trad(26 + 10, 0);
        vector<bool> isOk(26 + 10, false);
        uint64_t base = 1;
        for (uint64_t i = 0; i < line.size(); ++i) {
            if (!is_good(line[i]))
                continue ;
            uint64_t digit = get_digit(line[i]);
            // cout << digit << endl;
            if (!isOk[digit]) {
                trad[digit] = base;
                isOk[digit] = true;
                base = nextBase(base);
            }
        }

        base = max(base, uint64_t(2));
        uint64_t sum = 0;
        for (uint64_t i = 0; i < line.size(); ++i) {
            uint64_t digit = trad[get_digit(line[i])];
            sum *= base;
            sum += digit;
        }

        cout << "Case #" << (test+1) << ": " << sum << "\n";
    }
}
