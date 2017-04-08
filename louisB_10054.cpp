#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Edge {
    Edge(int _extr, int _id):
        extr(_extr), id(_id)  {}
    int extr;
    int id;
};

const int nbColorsMax = 50;
vector<vector<Edge>> beads;
int nbBeads;
vector<bool> seen;
vector<int> answer;

void eulerian_path(int node) {
    for (const auto& edge : beads[node]) {
        if (!seen[edge.id]) {
            seen[edge.id] = true;
            eulerian_path(edge.extr);
        }
    }
    answer.push_back(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbTests; cin >> nbTests;
    for (int test = 0; test < nbTests; ++test) {
        if (test != 0)
            cout << "\n";
        cout << "Case #" << test+1 << "\n";
        int nbBeads;
        cin >> nbBeads;
        beads.clear(); beads.resize(nbColorsMax);
        seen.clear(); seen.resize(nbBeads, false);
        answer.clear();
        for (int bead = 0; bead < nbBeads; ++bead) {
            int a, b;
            cin >> a >> b;
            a -= 1;
            b -= 1;
            assert(a < nbColorsMax);
            assert(b < nbColorsMax);
            beads[a].push_back(Edge(b, bead));
            beads[b].push_back(Edge(a, bead));
        }

        bool error = false;
        for (int color = 0; color < nbColorsMax; ++color) {
            if (beads[color].size() & 1) {
                error = true;
                break ;
            }
        }

        if (!error) {
            for (int color = 0; color < nbColorsMax; ++color) {
                if (beads[color].size() != 0) {
                    eulerian_path(color);
                    break ;
                }
            }
            if ((int)answer.size() != nbBeads+1) {
                error = true;
            }
        }

        if (error) {
            cout << "some beads may be lost\n";
            continue ;
        }

        for (int color = 0; color < (int)answer.size()-1; ++color) {
            cout <<  (answer[color]+1) << " " <<  (answer[color+1]+1) << "\n";
        }
    }
}
