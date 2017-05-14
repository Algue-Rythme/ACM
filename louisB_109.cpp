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

int64_t dot(const Point& a, const Point& b) {
    return a * b;
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

int64_t determinant(Point a, Point b) {
    return a.x*b.y - a.y*b.x;
}

typedef vector<Point> ConvexHull;

ConvexHull buildConvexHull(vector<Point>& points) {
    Point start = *min_element(begin(points), end(points),
    [](const Point& a, const Point& b){
        if (a.y != b.y)
            return a.y < b.y;
        return a.x < b.x;
    });
    sort(begin(points), end(points),
    [=](const Point& left, const Point& right){
        uint64_t dl = dot(Point(-1, 0), left - start);
        uint64_t dr = dot(Point(-1, 0), right - start);
        dl *= norm2(right - start);
        dr *= norm2(left - start);
        if (dl != dr)
            return dl > dr;
        if (left.y != right.y)
            return left.y < right.y;
        return left.x < right.x;
    });
    cout << "points:\n";
    for (const auto p : points) {
        cout << p.x << " " << p.y << "\n";
    }
    cout << "\n";
    ConvexHull hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    for (unsigned int i = 2; i < points.size(); ++i) {
        Point a = hull[hull.size() - 2];
        Point b = hull[hull.size() - 1];
        Point c = points[i];
        Point pred = c - a;
        Point next = c - b;
        int64_t det = determinant(pred, next);
        while (hull.size() >= 2 && det < 0) {
            hull.pop_back();
            b = a;
            a = hull[hull.size() - 2];
            pred = c - a;
            next = c - b;
            det = determinant(pred, next);
        }
        hull.push_back(c);
    }
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nbSites;
    while (cin >> nbSites) {
        if (nbSites == -1)
            break ;
        vector<Point> points(nbSites);
        for (int site = 0; site < nbSites; ++site) {
            cin >> points[site];
        }
        ConvexHull hull = buildConvexHull(points);
        cout << "Envelop:\n";
        for (const auto p : hull) {
            cout << p.x << " " << p.y << "\n";
        }
        cout << "\n";
    }
}
