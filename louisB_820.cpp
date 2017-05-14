#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbNodes;
    for (int test = 1; true; ++test) {
        cin >> nbNodes;
        if (nbNodes == 0)
            return 0;
        int source, target, nbEdges;
        cin >> source >> target >> nbEdges;
        source -= 1;
        target -= 1;
        vector<vector<int>> capacity(nbNodes, vector<int>(nbNodes, 0));
        for (int edge = 0; edge < nbEdges; ++edge) {
            int a, b, c;
            cin >> a >> b >> c;
            capacity[a-1][b-1] += c;
            capacity[b-1][a-1] += c;
        }
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
        cout << "Network " << test << "\n";
        cout << "The bandwidth is " << fullFlow << ".\n\n";
    }
}
