#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <queue>
#include <set>
#include <array>

using namespace std;

struct Edge
{
    Edge() {};
    Edge(int _id, int _weight, int _from):
    id(_id), weight(_weight), from(_from) {}
    int id;
    int weight;
    int from;
    inline bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

const int NEVER_DISCOVER = -1;
const int INFTY = 1000*1000*1000;
const int NO_FATHER = -1;

const int nbNodesMax = 10*1000 + 1;
array<int, nbNodesMax> closed_set;
array<vector<Edge>, nbNodesMax> comeFrom;
array<int, nbNodesMax> seen;
int testId = 0;

using Node = vector<Edge>;
using Graph = array<Node, nbNodesMax>;
Graph graph;

int dfs(const Edge& edge) {
    int node = edge.from;
    int seum = closed_set[edge.id] - closed_set[node];
    // cout << edge.from << " " << edge.id << " " << seum << "\n";
    if (seen[node] == testId)
        return seum;
    seen[node] = testId;
    for (const auto& edge : comeFrom[node]) {
        seum += dfs(edge);
    }
    return seum;
}

int dijkstra(int nbNodes, int departure, int arrival)
{
    priority_queue<Edge> openset;
    openset.push(Edge(departure, 0, departure));

    for (int node = 0; node < nbNodes; ++node)
        closed_set[node] = NEVER_DISCOVER;

    while (!openset.empty())
    {
        Edge current = openset.top();
        openset.pop();

        if (closed_set[arrival] != NEVER_DISCOVER
            && current.weight > closed_set[arrival]) {
            break ;
        }

        if (closed_set[current.id] != NEVER_DISCOVER
            && closed_set[current.id] < current.weight)
            continue ;

        comeFrom[current.id].emplace_back(current);

        if (closed_set[current.id] != NEVER_DISCOVER)
            continue ;
        closed_set[current.id] = current.weight;

        for (auto neighbour : graph[current.id]) {
            int newWeight = neighbour.weight + current.weight;
            if (closed_set[neighbour.id] == NEVER_DISCOVER) {
                openset.emplace(neighbour.id, newWeight, neighbour.from);
            }
        }
    }

    return 2*dfs(Edge(arrival, 0, arrival));
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int nbNodes, nbEdges;
    while (cin >> nbNodes >> nbEdges) {
        testId += 1;
        for (int node = 0; node < nbNodes; ++node)
            graph[node].clear();
        for (int node = 0; node < nbNodes; ++node)
            comeFrom[node].clear();
        for (int edge = 0; edge < nbEdges; ++edge)
        {
            int departure, arrival, weight;
            cin >> departure >> arrival >> weight;
            graph[departure].emplace_back(arrival, weight, departure);
            graph[arrival].emplace_back(departure, weight, arrival);
        }
        cout << dijkstra(nbNodes, 0, nbNodes-1) << "\n";
    }
}
