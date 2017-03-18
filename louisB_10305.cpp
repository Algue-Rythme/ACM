#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int seen = -1;
unsigned int nbNodes, nbEdges;
vector<vector<unsigned int>> graph;
vector<int> degIn;

void tri_topologique(unsigned int node) {
    cout << (node+1) << " ";
    degIn[node] = seen;
    for (unsigned int neighbor : graph[node]) {
        degIn[neighbor] -= 1;
        if (degIn[neighbor] == 0) {
            tri_topologique(neighbor);
        }
    }
}

int main() {
    while (cin >> nbNodes >> nbEdges) {
        if (nbNodes == 0 && nbEdges == 0)
            break ;

        graph.clear();
        degIn.clear();
        graph.resize(nbNodes);
        degIn.resize(nbNodes, 0);
        for (unsigned int edge = 0; edge < nbEdges; ++edge) {
            unsigned int a, b;
            cin >> a >> b;
            graph[a-1].push_back(b-1);
            degIn[b-1] += 1;
        }

        for (unsigned int node = 0; node < nbNodes; ++node) {
            if (degIn[node] == 0) {
                tri_topologique(node);
            }
        }

        cout << "\n";
    }
}
