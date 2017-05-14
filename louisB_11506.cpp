#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbNodes, nbEdges;
    while (true) {
        cin >> nbNodes >> nbEdges;
        if (nbNodes == 0 && nbEdges == 0)
            return 0;

        vector<vector<int>> capacity(nbNodes*2, vector<int>(nbNodes*2, 0));
        for (int node = 0; node < nbNodes-2; ++node) {
            int index, cost;
            cin >> index >> cost;
            index -= 1;
            capacity[index][index+nbNodes] += cost;
        }

        for (int edge = 0; edge < nbEdges; ++edge) {
            int j, k, cost;
            cin >> j >> k >> cost;
            j -= 1;
            k -= 1;
            capacity[j + nbNodes][k] += cost;
            capacity[k + nbNodes][j] += cost;
        }

        int source = nbNodes;
        int target = nbNodes-1;
        nbNodes *= 2;

        vector<vector<int>> flow(nbNodes, vector<int>(nbNodes, 0));
        int fullFlow = 0;
        while (true) {
            vector<int> father(nbNodes, -1);
            father[source] = source;
            queue<int> fifo;
            fifo.push(source);
            while (!fifo.empty()) {
                int node = fifo.front();
                fifo.pop();
                if (node == target)
                    break ;
                for (int v = 0; v < nbNodes; ++v) {
                    if (capacity[node][v] - flow[node][v] > 0 && father[v] == -1) {
                        fifo.push(v);
                        father[v] = node;
                    }
                }
            }
            if (father[target] == -1)
                break ;
            int minFlow = 1000;
            int node = target;
            while (node != source) {
                int son = node;
                node = father[node];
                minFlow = min(minFlow, capacity[node][son] - flow[node][son]);
            }
            fullFlow += minFlow;
            node = target;
            while (node != source) {
                int son = node;
                node = father[node];
                flow[node][son] += minFlow;
                flow[son][node] -= minFlow;
            }
        }

        cout << fullFlow << "\n";
    }
}
