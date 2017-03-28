#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <queue>
#include <set>
#include <bitset>

using namespace std;

struct Coord {
    Coord(int _h, int _w):
    h(_h), w(_w) {}
    int h, w;
};

vector<Coord> directions = {Coord(1, 0), Coord(-1, 0), Coord(0, 1), Coord(0, -1)};

const int NEVER_SEEN = -1;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int H, W;
    int test = 0;
    while (cin >> H >> W) {
        test += 1;
        if (H == 0 && W == 0)
            break ;
        /*if (test > 2)
        break;*/
        vector<vector<bool>> graph(H, vector<bool>(W*4, false));
        vector<vector<int>> seen(H, vector<int>(W*4, NEVER_SEEN));
        for (int h = 0; h < H; ++h) {
            string line;
            cin >> line;
            //cout << line << endl;
            for (int w = 0; w < W; ++w) {
                int i = int(line[w] - '0');
                if (line[w] >= 'a')
                    i = int(line[w] - 'a' + 10);
                for (int j = 0; j < 4; ++j) {
                    if (i & (1 << j)) {
                        graph[h][w*4 + 3 - j] = true;
                    }
                }
            }
        }

        int color = -1;
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < (int)graph[h].size(); ++w) {
                //cout << graph[h][w];
                if (seen[h][w] == NEVER_SEEN) {
                    color += 1;
                    queue<Coord> fifo;
                    bool nature = graph[h][w];
                    fifo.push(Coord(h, w));
                    seen[h][w] = color;
                    while (!fifo.empty()) {
                        Coord pos = fifo.front();
                        fifo.pop();
                        for (const auto& dir : directions) {
                            Coord voisin(pos.h + dir.h, pos.w + dir.w);
                            if (voisin.h < 0 || voisin.h >= H || voisin.w < 0 || voisin.w >= int(graph[h].size()))
                                continue ;
                            if (seen[voisin.h][voisin.w] == NEVER_SEEN
                            && nature == graph[voisin.h][voisin.w]) {
                                fifo.push(voisin);
                                seen[voisin.h][voisin.w] = color;
                            }
                        }
                    }
                }
            }
            //cout << "\n";
        }

        vector<set<int>> meta(color+1);
        vector<bool> isBlack(color+1, false);
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < (int)graph[h].size(); ++w) {
                //cout << seen[h][w] << " ";
                isBlack[seen[h][w]] = graph[h][w];
                for (const auto& dir : directions) {
                    Coord voisin(h + dir.h, w + dir.w);
                    if (voisin.h < 0 || voisin.h >= H || voisin.w < 0 || voisin.w >= int(graph[h].size())) {
                        meta[seen[h][w]].insert(-1);
                        continue ;
                    }
                    if (seen[voisin.h][voisin.w] == seen[h][w])
                        continue ;
                    meta[seen[h][w]].insert(seen[voisin.h][voisin.w]);
                }
            }
            //cout << endl;
        }

        vector<int> trous(6, 0);
        string code = "WAKJSD";
        for (int zone = 0; zone < (int)meta.size(); ++zone) {
            if (isBlack[zone]) {
                int count = 0;
                for (auto voisin : meta[zone]) {
                    if (voisin != -1 && meta[voisin].find(-1) == end(meta[voisin]))
                        count += 1;
                }
                trous[count] += 1;
            }
        }

        cout << "Case " << test << ": ";
        for (const auto& j : {1, 5, 3, 2, 4, 0}) {
            for (int i = 0; i < trous[j]; ++i) {
                cout << code[j];
            }
        }
        cout << "\n";
    }
}
