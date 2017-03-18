#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string line;
    bool open = false;
    while (getline(cin, line)) {
        string out;
        for (unsigned int i = 0; i < line.size(); ++i) {
            if (line[i] == '\"') {
                if (!open)
                    out += "``";
                else
                    out += "\'\'";
                open = !open;
            }  else {
                out.push_back(line[i]);
            }
        }
        cout << out << "\n";
    }
}
