#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    default_random_engine gen(446286);
    ios::sync_with_stdio(false);
    unsigned int n, nbTests;
    cin >> n >> nbTests;
    for (unsigned int test = 0; test < nbTests; ++test) {
        /*
        cout << (1u << n) << "\n";
        for (unsigned int i = 1; i <= (1u << (n-1)); ++i) {
            cout << i << " " << (2*i) << " " << (int(gen())%2000 - 1000) << "\n";
            cout << i << " " << (2*i+1) << " " << (int(gen())%2000 - 1000) << "\n";
        }*/
        cout << (n-1) << "\n";
        for (unsigned int i = 1; i < n; ++i) {
            cout << i << " " << n << " " << (int(gen())%2000 - 1000) << "\n";
        }
    }
    cout << "0\n";
}
