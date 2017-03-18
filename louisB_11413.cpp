#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int infty = 1000*1000*1000;

int main() {
    int nbVessels, nbContainers;
    while (cin >> nbVessels >> nbContainers) {
        vector<int> vessels(nbVessels+2, 0);
        for (int vessel = 1; vessel <= nbVessels; ++vessel) {
            int capacity;
            cin >> capacity;
            vessels[vessel] += capacity;
            vessels[vessel+1] = vessels[vessel];
        }

        vector<vector<int>> dyna(nbVessels+2, vector<int>(nbContainers, infty));
        for (int vessel = 0; vessel <= nbVessels; ++vessel) {
            dyna[vessel][0] = vessels[vessel];
        }

        for (int vessel = 0; vessel <= nbVessels; ++vessel) {
            for (int container = 1; container < nbContainers; ++container) {
                for (int pred = 0; pred < vessel; ++pred) {
                    int filling = vessels[vessel] - vessels[pred];
                    int other = dyna[pred][container-1];
                    int choice = max(filling, other);
                    dyna[vessel][container] = min(dyna[vessel][container], choice);
                }
            }
        }

        int best = dyna[nbVessels][nbContainers-1];
        printf("%d\n", best);
    }
}
