#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

const int INFINITY = 1000*1000*1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbNodes;
    while (cin >> nbNodes) {
        if (n == -1)
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
                graph[node-1].push_back(extr-1);
            }
        }

        vector<int> dyna(nbNodes, -INFINITY);
        dyna[start] = 100;
        for (int k = 1; k < nbNodes; ++k) {
            for (int node = 0; node < nbNodes; ++node) {
                for (const auto& edge : node) {
                    if (dyna[node] >= 0) {
                        dyna[edge.extr] = max(dyna[edge.extr], dyna[node] + energy[node]);
                    }
                }
            }
        }

        if (dyna[arrival] != -INFINITY)
            cout << "winnable\n";
        else {
            
        }
    }
}
