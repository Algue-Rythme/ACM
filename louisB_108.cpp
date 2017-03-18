#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

unsigned int n;
const unsigned int sizeMax = 100;
int cumul[sizeMax+2][sizeMax+2];

inline int eval(
    int lowLine,
    int lowColumn,
    int highLine,
    int highColumn) {
    return
        cumul[highLine][highColumn]
        - cumul[highLine][lowColumn]
        - cumul[lowLine][highColumn]
        + cumul[lowLine][lowColumn];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= n; ++j) {
            int v;
            cin >> v;
            cumul[i][j] += v;
            cumul[i][j] += cumul[i-1][j];
            cumul[i][j] += cumul[i][j-1];
            cumul[i][j] -= cumul[i-1][j-1];
        }
    }

    int sum = 0;
    for (unsigned int highLine = 1; highLine <= n; ++highLine) {
        for (unsigned int highColumn = 1; highColumn <= n; ++highColumn) {
            for (unsigned int lowLine = 0; lowLine < highLine; ++lowLine) {
                for (unsigned int lowColumn = 0; lowColumn < highColumn; ++lowColumn) {
                    sum = max(sum, eval(highLine, highColumn, lowLine, lowColumn));
                }
            }
        }
    }

    cout << sum << "\n";
}
