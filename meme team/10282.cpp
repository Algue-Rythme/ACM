#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

typedef vector<int> vectint;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    map<string, string> dict;
    string line;
    while (getline(cin, line)) {
        if (line.empty())
            break ;
        stringstream in(line);
        string word, trad;
        in >> word >> trad;
        dict[trad] = word;
    }

    string trad;
    while (cin >> trad) {
        if (dict.find(trad) == end(dict))
            cout << "eh\n";
        else
            cout << dict[trad] << "\n";
    }
}
