#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    Edge() = default;
    Edge(uint64_t _node, uint64_t _weight):node(_node), weight(_weight){}
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
    uint64_t node;
    uint64_t weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int nbNodes, nbEdges;
    while (cin >> nbNodes >> nbEdges) {
        if (nbNodes == 0)
            break;

        vector<vector<Edge>> graph(nbNodes);
        uint64_t totalWeight = 0;
        for (unsigned int edge = 0; edge < nbEdges; ++edge) {
            uint64_t x, y, z;
            cin >> x >> y >> z;
            graph[x].emplace_back(y, z);
            graph[y].emplace_back(x, z);
            totalWeight += z;
        }

        vector<bool> seen(nbNodes, false);

        uint64_t roadSelect = 0;
        priority_queue<Edge> wait;
        wait.push(Edge(0, 0));
        while (!wait.empty()) {
            Edge e = wait.top();
            wait.pop();
            if (seen[e.node])
                continue ;
            seen[e.node] = true;
            roadSelect += e.weight;
            for (const auto& neighbor : graph[e.node]) {
                if (!seen[neighbor.node]) {
                    wait.push(neighbor);
                }
            }
        }

        cout << (totalWeight-roadSelect) << "\n";
    }
}
