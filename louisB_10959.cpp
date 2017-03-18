#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int nbTests;
    cin >> nbTests;
    for (unsigned int test = 0; test < nbTests; ++test) {
        unsigned int nbNodes, nbEdges;
        cin >> nbNodes >> nbEdges;

        vector<vector<unsigned int>> graph(nbNodes);
        for (unsigned int edge = 0; edge < nbEdges; ++edge) {
            unsigned int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        vector<unsigned int> seen(nbNodes, 0);
        queue<unsigned int> wait;
        wait.push(0);
        seen[0] = 1;
        while (!wait.empty()) {
            unsigned int node = wait.front();
            wait.pop();

            for (unsigned int neighbor : graph[node]) {
                if (seen[neighbor] == 0) {
                    seen[neighbor] = seen[node] + 1;
                    wait.push(neighbor);
                }
            }
        }

        for (unsigned int node = 1; node < nbNodes; ++node) {
            cout << (seen[node]-1) << "\n";
        }

        if (test+1 < nbTests)
            cout << "\n";
    }
}
