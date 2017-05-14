#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

struct Point {
    Point() = default;
    Point(int64_t _x, int64_t _y): x(_x), y(_y) {}
    int64_t x;
    int64_t y;
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n == 0)
            break ;
        vector<Point> points(n+1);
        for (int i = 0; i < n; ++i) {
            cin >> points[i];
        }
        points[n] = points[0];

        Point pos;
        cin >> pos;

        bool parity = false;
        for (int i = 0; i < n; ++i) {
            if (min(points[i].x, points[i+1].x) <= pos.x && max(points[i].x, points[i+1].x) >= pos.x && points[i].y >= pos.y) {
                parity = !parity;
                //cout << "!";
            }
            //cout << "x";
        }
        //cout << "\n";

        if (parity) {
            cout << "T\n";
        } else {
            cout << "F\n";
        }
    }
}
