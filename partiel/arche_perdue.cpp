#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> planches;
int nbPlanches, tailleRavin;

const int INFTY = 1000;

bool isSuccess(int maxJump, vector<int> weak) {
    for (int way_id = 0; way_id < 2; ++way_id) {
        int pos = 0;
        int iPred = -1;
        for (int j = 0; j < nbPlanches; ++j) {

            if (planches[j] > pos + maxJump) {
                if (iPred == -1)
                    return false;
                pos = planches[iPred];
                weak[iPred] -= 1;
                if (planches[j] > pos + maxJump)
                    return false;
            }

            if (weak[j] > 1) {
                pos = planches[j];
                iPred = j;
            } else if (weak[j] != 0)
                iPred = j;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbTests;
    cin >> nbTests;
    for (int test = 0; test < nbTests; ++test) {
        cin >> nbPlanches >> tailleRavin;
        planches.resize(nbPlanches);
        vector<int> weak(nbPlanches, INFTY);
        for (int planche = 0; planche < nbPlanches; ++planche) {
            char c;
            cin >> c;
            if (c == 'S') {
                weak[planche] = 1;
            }
            //cout << c;
            cin >> c >> planches[planche];
            //cout << c << planches[planche] << "\n";
        }
        planches.push_back(tailleRavin);
        weak.push_back(INFTY);
        nbPlanches += 1;

        cout << "Case " << (test+1) << ": ";
        int maxOk = tailleRavin;
        int minNope = 0;
        while (maxOk - minNope > 1) {
            int mid = (maxOk + minNope)/2;
            bool tester = isSuccess(mid, weak);
            if (tester) {
                maxOk = mid;
            } else {
                minNope = mid;
            }
        }
        cout << maxOk << "\n";
    }
}
