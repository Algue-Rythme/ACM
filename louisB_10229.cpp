#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int64_t, int64_t> mem;

int64_t parity(int64_t n) {
    if (n & 1)
        return int64_t(-1);
    return int64_t(1);
}

int64_t fibo(int64_t n, int64_t m) {
    if (n <= 1)
        return n % m;
    if (n == 2)
        return 1 % m;
    if (mem.find(n) == mem.end()) {
        int64_t a = fibo((n >> 1) + 1, m);
        int64_t b = fibo((n - 1) >> 1, m);
        mem[n] = ( (a*a)%m - parity(n)*(b*b)%m + m) % m;
    }

    return mem[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n, m;
    while (cin >> n >> m) {
        mem.clear();
        cout << fibo(n, 1 << m) << "\n";
    }
}
