#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

enum OperationType {
    Insert,
    Delete,
    Replace,
    Nothing
};

struct Operation {
    Operation() = default;
    Operation(OperationType _type, int _i, int _j):
    type(_type), i(_i), j(_j) {}
    OperationType type;
    int i;
    int j;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    bool isFirst = true;
    while (getline(cin, a) && getline(cin, b)) {
        if (!isFirst)
            cout << "\n";
        isFirst = false;

        int n = max(a.size(), b.size()) + 1;
        const int maxDistance = 1000 * 1000;
        vector<vector<int>> dyna(n, vector<int>(n, maxDistance));
        vector<vector<Operation>> hist(n, vector<Operation>(n));

        dyna[0][0] = 0;
        for (int i = 1; i < n; ++i) {
            dyna[i][0] = i;
            dyna[0][i] = i;

            hist[i][0] = Operation(Delete, i-1, 0);
            hist[0][i] = Operation(Insert, 0, i-1);
        }

        for (int i = 1; i <= (int)a.size(); ++i) {
            for (int j = 1; j <= (int)b.size(); ++j) {

                if (a[i-1] == b[j-1]) {
                    dyna[i][j] = dyna[i-1][j-1];
                    hist[i][j] = Operation(Nothing, i-1, j-1);
                } else {
                    dyna[i][j] = dyna[i-1][j-1] + 1;
                    hist[i][j] = Operation(Replace, i-1, j-1);
                }

                int del = dyna[i-1][j] + 1;
                if (del < dyna[i][j]) {
                    dyna[i][j] = del;
                    hist[i][j] = Operation(Delete, i-1, j);
                }

                int insert = dyna[i][j-1] + 1;
                if (insert < dyna[i][j]) {
                    dyna[i][j] = insert;
                    hist[i][j] = Operation(Insert, i, j-1);
                }
            }
        }

        cout << dyna[a.size()][b.size()] << "\n";
        int i = a.size();
        int j = b.size();
        vector<Operation> path;
        while (i != 0 || j != 0) {
            Operation op = hist[i][j];
            path.push_back(op);
            i = op.i;
            j = op.j;
        }

        int delta = 1;
        int num = 1;
        for_each(path.rbegin(), path.rend(),
        [&](const Operation& op){
            int i = op.i;
            int j = op.j;
            if (op.type == Nothing)
                return ;
            cout << num << " ";
            switch (op.type) {
                case Insert:
                cout << "Insert " << i+delta << "," << b[j] << "\n";
                delta += 1;
                break ;

                case Delete:
                cout << "Delete " << i+delta << "\n";
                delta -= 1;
                break ;

                case Replace:
                cout << "Replace " << i+delta << "," << b[j] << "\n";
                break ;

                default:
                break ;
            }
            num += 1;
        });
    }
}
