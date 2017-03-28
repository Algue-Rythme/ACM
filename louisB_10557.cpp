#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

const int INFTY = 1000*1000*1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbNodes;
    while (cin >> nbNodes) {
        if (nbNodes == -1)
            break ;

        const int start = 0;
        const int arrival = nbNodes-1;

        vector<vector<int>> graph(nbNodes);
        vector<int> energy(nbNodes);
        for (int node = 0; node < nbNodes; ++node) {
            int nbNeighbours;
            cin >> energy[node] >> nbNeighbours;
            for (int neighbour = 0; neighbour < nbNeighbours; ++neighbour) {
                int extr;
                cin >> extr;
                graph[node].push_back(extr-1);
            }
        }

        vector<int> dyna(nbNodes, -INFTY);
        dyna[start] = 100;
        for (int k = 1; k < nbNodes; ++k) {
            for (int node = 0; node < nbNodes; ++node) {
                for (const auto& edge : graph[node]) {
                    if (dyna[node] > 0) {
                        dyna[edge] = max(dyna[edge], dyna[node] + energy[node]);
                    }
                }
            }
        }

        if (dyna[arrival] > 0)
            cout << "winnable\n";
        else {
            vector<vector<bool>> isOk(nbNodes, vector<bool>(nbNodes, false));
            for (int node = 0; node < nbNodes; ++node) {
                for (const auto& edge : graph[node]) {
                    isOk[node][edge] = true;
                }
            }

            for (int k = 0; k < nbNodes; ++k) {
                for (int i = 0; i < nbNodes; ++i) {
                    for (int j = 0; j < nbNodes; ++j) {
                        isOk[i][j] = isOk[i][j] | (isOk[i][k] & isOk[k][j]);
                    }
                }
            }

            for (int node = 0; node < nbNodes; ++node) {
                for (const auto& edge : graph[node]) {
                    if (dyna[node] > 0) {
                        int newWeight = dyna[node] + energy[node];
                        if (dyna[edge] < newWeight && isOk[edge][arrival]) {
                            cout << "winnable\n";
                            goto nextTest;
                        }
                    }
                }
            }

            cout << "hopeless\n";
            nextTest: ;
        }
    }
}
