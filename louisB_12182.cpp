#include <algorithm>
#include <iostream>
#include <vector>

#define _DEBUG_

using namespace std;

struct Edge {
    Edge() = default;
    Edge(unsigned int _extr, int _p): extr(_extr), p(_p){}
    unsigned int extr;
    int p;
};

const unsigned int maxRoads = 100 * 1000;
const unsigned int nbNodesMax = 2*maxRoads + 1;
unsigned int nbTests = 0;
vector<unsigned int> graph[nbNodesMax];
Edge edges[nbNodesMax];
unsigned int mask[nbNodesMax];
int dyna[nbNodesMax];

int dfs(unsigned int pred, unsigned int node) {
    if (mask[node] == nbTests)
        return dyna[node];

    mask[node] = nbTests;
    int cur = 0;
    dyna[node] = 0;
    for (unsigned int son : graph[node]) {
        const auto& edge = edges[son];
        cur = max(cur, dfs(node, edge.extr));
        int subtree = dyna[edge.extr] + edge.p;
        if (edge.extr != pred && subtree > 0)
            dyna[node] += subtree;
    }

    return max(dyna[node], cur);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    unsigned int nbRoads;
    while (cin >> nbRoads) {
        if (nbRoads == 0)
            return 0;

        // READ GRAPH
        nbTests += 1;
        for (unsigned int road = 0; road < nbRoads; ++road) {
            unsigned int a, b;
            int p;
            cin >> a >> b >> p;
            graph[a].push_back(2*road);
            graph[b].push_back(2*road+1);
            edges[2*road] = Edge(b, p);
            edges[2*road+1] = Edge(a, p);
        }

        // SOLVE PROBLEM
        int optim = 0;
        for (unsigned int road = 0; road < 2*nbRoads; ++road) {
            optim = max(optim, dfs(2*nbNodesMax, edges[road].extr));
        }
        cout << optim << "\n";

        // CLEAR GRAPH
        for (unsigned int road = 0; road < 2*nbRoads; ++road) {
            graph[edges[road].extr].clear();
        }
    }
}
