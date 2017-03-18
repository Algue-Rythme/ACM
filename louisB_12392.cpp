#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <vector>

using namespace std;

vector<int> table(int('z'-'a') + 1, -1);
vector<char> symbols;

function<int ()> parse(istream_iterator<char>& it) {

    char var = *it;

    if (var >= 'a' && var <= 'z') {
        symbols.push_back(var);
        return [=](){
            return table[int(var - 'a')];
        };
    }

    if (var != '(')
        throw runtime_error("Parenthesis expected here");

    auto e1 = parse(++it);
    char op = *(++it);
    auto e2 = parse(++it);

    if (*(++it) != ')')
        throw runtime_error("Bad parenthesis matching");

    if (op == '+')
        return [=](){
            return e1() + e2();
        };

    if (op == '*')
        return [=](){
            return e1() * e2();
        };

    return [=](){
        return e1() - e2();
    };
}

int main() {
    unsigned int nbUnknows;
    while (cin >> nbUnknows) {
        if (nbUnknows == 0)
            break ;

        symbols.clear();
        vector<int> vars(nbUnknows);
        for (unsigned int unknow = 0; unknow < nbUnknows; ++unknow) {
            cin >> vars[unknow];
        }

        int target;
        cin >> target;

        istream_iterator<char> it(cin);
        auto eval = parse(it);

        bool ok = false;
        sort(begin(vars), end(vars));
        do {
            for (unsigned int var = 0; var < symbols.size(); ++var) {
                table[int(symbols[var] - 'a')] = vars[var];
            }

            int value = eval();
            if (value == target) {
                ok = true;
                break ;
            }

        } while(next_permutation(begin(vars), end(vars)));

        if (ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
