#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    for (int test = 1; true ; ++test) {
        vector<int> missiles;
        do {
            int missile;
            cin >> missile;
            missiles.push_back(missile);
        } while (missiles.back() != -1);
        missiles.pop_back();
        if (missiles.empty())
            break ;
        if (test != 1)
            cout << "\n";

        multimap<int, int> sequences;
        auto compSeq = [&](const pair<int, int>& seqleft, const pair<int, int>& seqright){
            return seqleft.second < seqright.second;
        };
        for (int missileID = missiles.size()-1; missileID >= 0; --missileID) {
            int missile = missiles[missileID];
            auto last = sequences.upper_bound(missile);
            auto select = max_element(begin(sequences), last, compSeq);
            if (select == last)
                sequences.insert(std::pair<int, int>(missile, 1));
            else {
                int longuest = select->second;
                sequences.insert(std::pair<int, int>(missile, longuest + 1));
            }
        }

        auto select = max_element(begin(sequences), end(sequences), compSeq);
        int longuest = select->second;
        cout << "Test #" << test << ":\n";
        cout << "  maximum possible interceptions: " << longuest << "\n";
    }
}
