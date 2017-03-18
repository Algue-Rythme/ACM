#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>

using namespace std;

int main() {
    array<bool, 32> isPrime; isPrime.fill(true);
    for (int n = 2; n < int(isPrime.size()); ++n) {
        for (int j = 2; j*j <= n; ++j) {
            if (n % j == 0) {
                isPrime[n] = false;
                break ;
            }
        }
    }

    int circleSize;
    int caseNum = 1;

    array<int, 16> stack; stack.fill(0);
    stack[0] = 1;
    array<bool, 17> used; used.fill(false);
    used[stack[0]] = true;

    /*
    array<bool, 17> mem; mem.fill(false);
    array<vector< array<int, 16> >, 17> output;*/

    while (scanf("%d", &circleSize) != EOF) {
        if (caseNum != 1)
            printf("\n");
        printf("Case %d:\n", caseNum);
        caseNum += 1;

        if (circleSize == 1)
            printf("1\n");
        if (circleSize % 2 != 0)
            continue ;

        /*
        if (mem[circleSize]) {
            for (const auto& s : output[circleSize]) {
                for (int i = 0; i < circleSize; ++i) {
                    printf("%d%c", s[i], i+1 == circleSize ? '\n' : ' ');
                }
            }
            continue ;
        }

        mem[circleSize] = true; */

        int pos = 1;

        while (pos != 0) {

            if (pos == circleSize) {
                if (isPrime[stack[pos-1] + 1]) {
                    for (int i = 0; i < circleSize; ++i) {
                        printf("%d%c", stack[i], i+1 == circleSize ? '\n' : ' ');
                    }
                    // output[circleSize].push_back(stack);
                }
                pos -= 1;
                continue ;
            }

            used[stack[pos]] = false;

            int i = stack[pos] + 1;
            while (i <= circleSize &&
                  (used[i] || !isPrime[stack[pos-1] + i]))
                ++i;

            if (i <= circleSize) {
                stack[pos] = i;
                used[i] = true;
                pos += 1;
            } else {
                stack[pos] = 0;
                pos -= 1;
            }
        }
    }
}
