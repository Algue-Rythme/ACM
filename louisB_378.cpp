#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

const double INFTY = 1e9;

struct Point {
    Point() = default;
    Point(int64_t _x, int64_t _y): x(_x), y(_y) {}
    int64_t x;
    int64_t y;
    double coeff() {
        if (x == 0)
            return (y > 0)? INFTY : -INFTY;
        return double(y) / double(x);
    }
};

Point origin(0, 0);

Point operator-(const Point& a, const Point& b) {
    return Point(b.x - a.x, b.y - a.y);
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int64_t operator*(const Point& a, const Point& b) {
    return a.x*b.x + a.y*b.y;
}

int64_t norm2(const Point& p) {
    return p * p;
}

bool isColinear(const Point& v1, const Point& v2) {
    int64_t dot = v1 * v2;
    int64_t n1 = norm2(v1);
    int64_t n2 = norm2(v2);
    return dot*dot == n1*n2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(5) << fixed << showpoint;

    int nbTests;
    cin >> nbTests;
    cout << "INTERSECTING LINES OUTPUT\n";
    for (int test = 0; test < nbTests; ++test) {
        Point p1, p2;
        Point q1, q2;
        cin >> p1 >> p2 >> q1 >> q2;

        Point v1 = p2 - p1;
        Point v2 = q2 - q1;

        if (isColinear(v1, v2)) {
            if (isColinear(q1 - p1, q1 - p2)) {
                cout << "LINE\n";
            } else {
                cout << "NONE\n";
            }
        } else {
            double a = v1.coeff();
            double c = v2.coeff();

            double b = p1.y - a*p1.x;
            double d = q1.y - c*q1.x;;

            double x = (d - b)/(a - c);
            double y = a*x + b;
            cout << "POINT " << x << " " << y << "\n";
        }
    }

    cout << "END OF OUTPUT\n";
}
