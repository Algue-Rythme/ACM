#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int main() {
    unsigned int nbCountries;
    cin >> nbCountries;
    map<string, unsigned int> girls;
    for (unsigned int country = 0; country < nbCountries; ++country) {
        string countryName; cin >> countryName;
        cin.ignore(75, '\n');
        if (girls.find(countryName) == end(girls))
            girls[countryName] = 0;
        girls[countryName] += 1;
    }
    for (auto girl : girls) {
        cout << girl.first << " " << girl.second << "\n";
    }
}
