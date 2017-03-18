#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>

using namespace std;

const int nbNodesMax = 500;
int nbNodes, nbSatellites;
int father[nbNodesMax+1];
int prof[nbNodesMax+1];
int64_t x[nbNodesMax+1];
int64_t y[nbNodesMax+1];

struct Edge {
    Edge() = default;
    Edge(int _a, int _b, int _weight):
        a(_a), b(_b), weight(_weight) {}
    int a;
    int b;
    int64_t weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

inline int distance_between(int i, int j) {
    int64_t deltaX = x[j] - x[i];
    int64_t deltaY = y[j] - y[i];
    return deltaX*deltaX + deltaY*deltaY;
}

int get_father(int node) {
    if (father[node] != node) {
        father[node] = get_father(father[node]);
    }
    return father[node];
}

double bounded_union_find() {
    vector<Edge> edges; edges.reserve(nbNodes*(nbNodes-1)/2);
    for (int i = 0; i < nbNodes; ++i) {
        for (int j = 0; j < i; ++j) {
            edges.push_back(Edge(i, j , distance_between(i, j)));
        }
    }
    sort(begin(edges), end(edges));

    int64_t dMin = 0;
    int nbComp = nbNodes;
    for (const auto& e : edges) {

        int fa = get_father(e.a);
        int fb = get_father(e.b);

        if (fa != fb) {
            father[fa] = fb;
            nbComp -= 1;
            dMin = e.weight;
        }

        if (nbSatellites >= nbComp || nbComp == 1)
            break ;
    }

    return sqrt(dMin);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << showpoint << setprecision(2);

    int nbTests;
    cin >> nbTests;
    for (int test = 0; test < nbTests; ++test) {
        cin >> nbSatellites >> nbNodes;
        for (int node = 0; node < nbNodes; ++node) {
            prof[node] = node;
            father[node] = node;
            cin >> x[node] >> y[node];
        }

        cout << bounded_union_find() << "\n";
    }
}
