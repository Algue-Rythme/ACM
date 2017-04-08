#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 0)
            break;
        int best = -1;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            sum += a;
            if (sum < 0) {
                sum = 0;
            } else if (best < sum) {
                best = sum;
            }
        }

        if (best == -1)
            cout << "Loose.\n";
        else
            cout << "Winning with " << best << ".\n";
    }
}
