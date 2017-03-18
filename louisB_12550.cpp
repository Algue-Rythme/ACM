#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

unsigned int solve(const array<unsigned int, 4>& mem) {
    /*//
    c = ua + vb
    d = ub + vc
    //*/

    /// ...
}

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream in(line);
        unsigned int waterfallDistance, jumpPower;
        in >> waterfallDistance >> jumpPower;
        unsigned int unreachableDistance = waterfallDistance + 1;
        array<unsigned int, 4> mem;
        for (unsigned int meter = 0; meter <= waterfallDistance; ++meter) {
            unsigned int speed;
            if (!(in >> speed)) {
                speed = solve(mem);
            }

            if (speed <= jumpPower) {
                unreachableDistance -= 1;
            } else {
                if (meter == 0)
                    cout << "The spider is going to fall!\n";
                else
                    cout << unreachableDistance << "\n";
                break ;
            }

            for (unsigned int i = 1; i < mem.size(); ++i)
                mem[i-1] = mem[i];
            mem[mem.size()-1] = speed;
        }

        if (unreachableDistance == 0) {
            cout << "The spider may fall!\n";
        }
    }
}
