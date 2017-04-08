#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbCodes;
    cin >> nbCodes;
    cin.ignore(1000, '\n');
    for (int code = 0; code < nbCodes; ++code) {
        cout << "Case " << (code+1) << ": ";
        string line;
        getline(cin, line);
        line += "@";
        int occ = 0;
        char pred = '$';
        for (int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c >= '0' && c <= '9') {
                occ *= 10;
                occ += (c - '0');
            } else {
                for (int j = 0; j < occ; ++j) {
                    cout << pred;
                }
                occ = 0;
                pred = c;
            }
        }
        cout << "\n";
    }
}
