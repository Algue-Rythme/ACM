#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string word;
    while (getline(cin, word)) {
        if (word == ".")
            return 0;
        for (int i = 1; i <= (int)word.size(); ++i) {
            if (word.size()%i == 0) {
                bool is_good = true;
                for (int j = i; j < (int)word.size(); ++j) {
                    if (word[j] != word[j % i]) {
                        is_good = false;
                        //cout << word[j] << " " << word[j % i] << "\n";
                        break ;
                    }
                }
                if (!is_good)
                    continue ;
                cout << (int(word.size())/i) << "\n";
                break ;
            }
        }
    }
}
