#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstdint>

using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream in(line);
        int64_t a, b;
        in >> a >> b;
        cout << abs(b - a) << "\n";
    }
}
