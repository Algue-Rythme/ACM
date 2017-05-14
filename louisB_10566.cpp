#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

double x, y, c;

bool eval(double D) {
    double dY = sqrt(y*y - D*D);
    double dX = sqrt(x*x - D*D);
    double ratio = c/dX + c/dY;
    //cout << ratio << "\n";
    return !(ratio < 1.); // != ratio >= 1.
}

double dichotomy(double inf, double sup, double epsilon) {
    double middle = (sup + inf)/2.;
    while (sup - inf > epsilon) {
        bool isInf = eval(middle);
        if (isInf)
            sup = middle;
        else
            inf = middle;
        middle = (sup + inf)/2.;
    }
    return middle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3) << showpoint;
    while (cin >> x >> y >> c) {
        cout << dichotomy(0., max(x, y), 1e-6) << "\n";
    }
}
