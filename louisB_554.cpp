#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

string convert(const string& message, int k) {
    string trad = message;
    for (int i = 0; i < (int)trad.size(); ++i) {
        int num = (trad[i] == ' ')? 0 : trad[i] - 'A' + 1;
        num += k;
        num %= 27;
        if (num == 0)
            trad[i] = ' ';
        else
            trad[i] = char(num + 'A' - 1);
    }
    return trad;
}

vector<string> get_subwords(const string& trad) {
    int beginning = 0;
    vector<string> temp;
    for (int i = 0; i < (int)trad.size(); ++i) {
        if (trad[i] == ' ') {
            string subword = trad.substr(beginning, i - beginning);
            temp.push_back(subword);
            beginning = i+1;
        }
    }
    if (beginning < (int)trad.size())
        temp.push_back(trad.substr(beginning, (int)trad.size()));
    return temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    set<string> dict;
    string word;
    while (getline(cin, word)) {
        if (word == "#")
            break ;
        dict.insert(word);
    }

    string message;
    getline(cin, message);
    int best = 0;
    int best_k = 0;
    for (int k = 0; k <= 26; k++) {
        string trad = convert(message, k);
        // cout << trad << "\n";
        vector<string> subwords = get_subwords(trad);
        int count = 0;
        for (const auto& subword : subwords) {
            //cout << subword << " ";
            if (dict.find(subword) != dict.end()) {
                count += 1;
                if (count > best) {
                    best = count;
                    best_k = k;
                }
            }
        }
        //cout << "\n";
    }

    string answer = convert(message, best_k);
    int pos = 0;
    for (const auto& subword : get_subwords(answer)) {
        int i = pos + subword.size() + 1;
        if (pos != 0) {
            if (i > 60) {
                cout << "\n";
                pos = subword.size();
            } else {
                cout << " ";
                pos = i;
            }
        } else {
            pos = subword.size();
        }
        cout << subword;
    }
    cout << "\n";
}
