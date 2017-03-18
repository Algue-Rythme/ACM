#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>
#include <queue>

using namespace std;

const int NEVER_SEEN = -1;

struct Edge {
    Edge() = default;
    Edge(int _extr, int _weight):
        extr(_extr), weight(_weight) {}
    int extr;
    int64_t weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbTests;
    cin >> nbTests;
    for (int test = 0; test < nbTests; ++test) {
        if (test != 0)
            cout << "\n";

        int nbNodes, exitCell, timeLimit, nbEdges;
        cin >> nbNodes >> exitCell >> timeLimit >> nbEdges;

        vector<vector<Edge>> graph(nbNodes);
        for (int edge = 0; edge < nbEdges; ++edge) {
            int a, b, weight;
            cin >> a >> b >> weight;
            graph[b-1].push_back(Edge(a-1, weight));
        }

        vector<int> seen(nbNodes, NEVER_SEEN);
        priority_queue<Edge> fifo;
        fifo.push(Edge(exitCell-1, 0));
        int isOut = 0;
        while (!fifo.empty()) {
            Edge e = fifo.top();
            fifo.pop();

            if (seen[e.extr] != NEVER_SEEN)
                continue ;
            seen[e.extr] = e.weight;

            if (seen[e.extr] <= timeLimit)
                isOut += 1;

            for (const auto& neighbor : graph[e.extr]) {
                if (seen[neighbor.extr] == NEVER_SEEN) {
                    fifo.push(Edge(neighbor.extr, neighbor.weight + e.weight));
                }
            }
        }

        cout << isOut << "\n";
    }
}
