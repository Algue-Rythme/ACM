#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    Edge(int _extr, int _id):
        id(_id), extr(_extr) {}
    int extr;
    int id;
};

int nbColorsMax;
const int nbColorsMax = 50 + 1;
array<vector<int>, nbColorsMax> colors;
vector<vector<int>> beads;
int nbBeads;
vector<bool> seen;

void eulerian_path() {
    // ...
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbTests; cin >> nbTests;
    for (int test = 0; test < nbTests; ++test) {
        int nbBeads;
        cin >> nbBeads;
        beads.clear(); beads.resize(nbBeads+1);
        for (const auto& color : colors)
            color.clear();
        seen.clear(); seen.resize(2*nbBeads+1, false);
        for (int bead = 1; bead <= nbBeads; ++bead) {
            int a, b;
            cin >> a >> b;
            beads[bead].push_back(Edge(a, bead));
            colors[a].push_back(Edge(bead, bead));
            beads[bead].push_back(Edge(b, bead + nbBeads));
            colors[b].push_back(Edge(bead, bead + nbBeads));
        }
        eulerian_path();
    }
}
