#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
    Edge() = default;
    Edge(int _a, int _b): a(_a), b(_b){}
    int a;
    int b;
    bool operator<(const Edge& other) const {
        int c = min(a, b);
        int d = min(other.a, other.b);
        int e = max(a, b);
        int f = max(other.a, other.b);
        if (c != d)
            return c < d;
        return e < f;
    }
};

int nbNodes;
vector<vector<Edge>> graph;
vector<bool> seen;

set<Edge> criticals;
vector<Edge> visited;

void dfs(int from, int node) {
    if (seen[node]) {
        //cout << "occurs !\n";
        int pred = visited.size()- 1;
        while (pred >= 0 && visited[pred].a != node) {
            //cout << visited[pred].a << " " << visited[pred].b << "\n";
            criticals.erase(visited[pred]);
            pred -= 1;
        }
        if (pred >= 0) {
            //cout << visited[pred].a << " " << visited[pred].b << "\n";
            criticals.erase(visited[pred]);
        }
        return ;
    }
    seen[node] = true;
    for (const auto& edge : graph[node]) {
        if (edge.b != from && criticals.find(edge) != end(criticals)) {
            visited.push_back(edge);
            dfs(node, edge.b);
            visited.pop_back();
        }
    }
}

int main() {
    while (cin >> nbNodes) {
        graph.clear(); graph.resize(nbNodes);
        criticals.clear();
        seen.clear(); seen.resize(nbNodes, false);
        for (int node = 0; node < nbNodes; ++node) {
            int numero, nbNeighbours;
            cin >> numero; cin.ignore(42, '(');
            cin >> nbNeighbours; cin.ignore(42, ')');
            graph[numero].resize(nbNeighbours);
            for (int neighbour = 0; neighbour < nbNeighbours; ++neighbour) {
                int extr;
                cin >> extr;
                Edge edge(numero, extr);
                graph[numero][neighbour] = edge;
                criticals.insert(edge);
            }
        }

        for (int node = 0; node < nbNodes; ++node)
            dfs(-1, node);

        cout << criticals.size() << " critical links\n";

        for (const auto& edge : criticals) {
            cout << min(edge.a, edge.b) << " - " << max(edge.a, edge.b) << "\n";
        }

        cout << "\n";
    }
}
