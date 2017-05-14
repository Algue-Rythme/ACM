#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        const int nbNodes = 10 + 26 + 2;
        vector<vector<int>> capacity(nbNodes, vector<int>(nbNodes, 0));

        int source = 0;
        int target = 1;
        int flowMax = 0;
        for (int i = 0; ; ++i) {
            string line;
            getline(cin, line);
            if (line.empty()) {
                if (i == 0)
                    return 0;
                break ;
            }
            istringstream in(line);
            //cout << line << endl;
            char app;
            int nbExemp;
            in >> app >> nbExemp;
            //cout << app << endl;
            int appNum = int(app - 'A') + 2;
            // cout << appNum << " " << nbExemp << endl;
            capacity[source][appNum] += nbExemp;
            flowMax += nbExemp;
            char computer;
            while(true) {
                in >> computer;
                //cout << computer << endl;
                if (computer == ';')
                    break ;
                int computerNum = int(computer - '0') + 2 + 26;
                //cout << computerNum << endl;
                capacity[appNum][computerNum] = 1;
                capacity[computerNum][target] = 1;
            }
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

        if (fullFlow < flowMax)
            cout << "!\n";
        else {
            for (int computer = 26+2; computer < 26+2+10; ++computer) {
                bool assigned = false;
                for (int app = 2; app < 2 + 26; ++app) {
                    if (flow[app][computer] - flow[computer][app]) {
                        cout << char(app-2+'A');
                        assigned = true;
                        break ;
                    }
                }
                if (!assigned)
                    cout << "_";
            }
            cout << "\n";
        }
    }
}
