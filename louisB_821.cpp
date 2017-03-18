#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>
#include <bitset>
#include <iomanip>

using namespace std;

const int nbNodesMax = 101;
const int infinity = 1000 * 1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << showpoint << setprecision(3);

    for (int test = 1; true; ++test) {
        vector<vector<int>> mat(nbNodesMax, vector<int>(nbNodesMax, infinity));
        bitset<nbNodesMax> inGraph;
        for (int edge = 0; true ; ++edge) {
            int a, b;
            cin >> a >> b;
            if (a == 0 && b == 0) {
                if (edge == 0)
                    return 0;
                break ;
            }

            mat[a-1][b-1] = 1;

            inGraph[a-1] = true;
            inGraph[b-1] = true;
            mat[a-1][a-1] = 0;
            mat[b-1][b-1] = 0;
        }

        for (int k = 0; k < nbNodesMax; ++k) {
            for (int i = 0; i < nbNodesMax; ++i) {
                for (int j = 0; j < nbNodesMax; ++j) {
                    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < nbNodesMax; ++i) {
            if (!inGraph[i])
                continue ;
            for (int j = 0; j < nbNodesMax; ++j) {
                if (inGraph[j]) {
                    sum += mat[i][j];
                }
            }
        }

        int n = inGraph.count() * (inGraph.count() - 1);
        double average = double(sum) / double(n);

        cout << "Case " << test << ": average length between pages = " << average << " clicks\n";
    }
}
