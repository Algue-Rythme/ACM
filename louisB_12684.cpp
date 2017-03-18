#include <algorithm>
#include <array>
#include <iostream>
#include <set>

using namespace std;

const int nbColours = 5;
const int WHITE = 0;
const int nbNodesMax = 100;
array<int, nbNodesMax+1> seen;
array<int, nbNodesMax+1> color;
array<set<int>, nbNodesMax+1> graph;
int nbNodes = 0;

bool coloring(int node) {
    if (node > nbNodes)
        return true;
    if (seen[node])
        return true;

    seen[node] = true;
    array<bool, nbColours> usable; usable.fill(true);
    for (const auto& neighbour : graph[node]) {
        if (seen[neighbour]) {
            usable[color[neighbour]] = false;
        }
    }

    for (int choice = 1; choice < nbColours; ++choice) {
        if (usable[choice]) {
            color[node] = choice;
            bool isOk = coloring(node+1);
            if (isOk) {
                seen[node] = false;
                return true;
            }
        }
    }

    seen[node] = false;
    return false;
}

void compute() {
    for (int i = 1; i <= nbNodes; ++i) {
        if (color[i] == WHITE)
            coloring(i);
        cout << i << " " << color[i] << "\n";
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    color.fill(WHITE);
    int cur;
    while (cin >> cur) {
        char c = cin.get();
        if (c == '-') {
            int b;
            int a = cur;
            cin >> b;
            graph[a].insert(b);
            graph[b].insert(a);
            //cout << a << "-" << b << "\n";
        }
        else {
            compute();

            color.fill(WHITE);
            for (auto& node : graph)
                node.clear();
            nbNodes = cur;
        }
    }

    compute();
}
