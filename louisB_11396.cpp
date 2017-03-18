#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int seen = -1;
unsigned int nbNodes;
vector<vector<unsigned int>> graph;
vector<int> color;

const int white = 0;
const int red = 1;
const int blue = 2;

bool isBipartite(unsigned int node, bool actualColor) {
    if (color[node] != white && color[node] != actualColor)
        return false;
    if (color[node] != white)
        return true;
    color[node] = actualColor;
    for (unsigned int neighbor : graph[node]) {
        bool isOk = isBipartite(neighbor, !actualColor);
        if (!isOk)
            return false;
    }
    return true;
}

int main() {
    while (cin >> nbNodes) {
        if (nbNodes == 0)
            break ;

        graph.clear();
        graph.resize(nbNodes);
        color.clear();
        color.resize(nbNodes);

        unsigned int a, b;
        while (cin >> a >> b) {
            if (a == 0 && b == 0)
                break ;
            graph[a-1].push_back(b-1);
            graph[b-1].push_back(a-1);
        }

        if (isBipartite(0, true))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
