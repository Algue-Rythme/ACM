#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<vector<unsigned int>> Graph;
Graph graph;
vector<unsigned int> lastVisit;
vector<bool> seen;
unsigned int nbNodes, nbEdges;

void searchCFC(unsigned int node) {
    if (seen[node])
        return ;
    seen[node] = true;
    for (unsigned int neighbor : graph[node])
        searchCFC(neighbor);
    lastVisit.push_back(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int nbTests;
    cin >> nbTests;
    for (unsigned int test = 0; test < nbTests; ++test) {
        unsigned int nbNodes, nbEdges;
        cin >> nbNodes >> nbEdges;

        graph.clear();
        lastVisit.clear();
        seen.clear();

        graph.resize(nbNodes);
        seen.resize(nbNodes, false);

        for (unsigned int edge = 0; edge < nbEdges; ++edge) {
            unsigned int a, b;
            cin >> a >> b;
            graph[a-1].push_back(b-1);
        }

        for (unsigned int node = 0; node < nbNodes; ++node)
            searchCFC(node);

        seen.assign(nbNodes, false);

        unsigned int nbDominos = 0;
        for (unsigned int node = nbNodes; node >= 1; --node) {
            if (!seen[lastVisit[node-1]]) {
                searchCFC(lastVisit[node-1]);
                nbDominos += 1;
            }
        }

        cout << nbDominos << "\n";
    }
}
