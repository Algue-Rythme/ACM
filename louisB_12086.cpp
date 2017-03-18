#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <array>

using namespace std;

const int nbTests = 3;
const int maxN = 200*1000;
array<int, maxN+1> acc;
int N;

inline int LSB(int pos) {
    return pos & (-pos);
}

void add(int pos, int value) {
    while (pos <= N) {
        acc[pos] += value;
        pos += LSB(pos);
    }
}

int sumto(int pos) {
    int s = 0;
    while (pos > 0) {
        s += acc[pos];
        pos -= LSB(pos);
    }

    return s;
}

int request(int a, int b) {
    return sumto(b) - sumto(a-1);
}

int get(int x) {
    return request(x, x);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    for (int test = 1; test <= nbTests; ++test) {
        cin >> N;
        if (N == 0)
            return EXIT_SUCCESS;

        if (test != 1)
            cout << "\n";
        cout << "Case " << test << ":\n";

        acc.fill(0);
        for (int i = 0; i < N; ++i) {
            int v;
            cin >> v;
            add(i+1, v);
        }

        while (true) {
            string code;
            cin >> code;
            if (code == "END")
                break ;

            if (code == "S") {
                int x, r;
                cin >> x >> r;
                add(x, -get(x));
                add(x, r);
            } else {
                int a, b;
                cin >> a >> b;
                int answer = request(a, b);
                cout << answer << "\n";
            }
        }
    }
}
