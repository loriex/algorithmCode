#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define N 16
class Solver {
    int map[N][N];
    int n;
    int count;
    void clear() {
        memset(map, 0, sizeof(map));
        n = count = 0;
    }
    void dfs(vector<int> vec, int depth, int maxLen, int sumLen) {
        int len = vec.size();
        if (len <= 1) {
            if (sumLen > 2 * maxLen)
                ++count;
            return;
        }
        for (int j = 1; j < len; ++j)
            if (map[vec[0]][vec[j]]) {
                vector<int> nvec;
                for (int k = 1; k < len; ++k)
                    if (k != j)
                        nvec.push_back(vec[k]);
                dfs(nvec, depth + 1, max(maxLen, map[vec[0]][vec[j]]), sumLen + map[vec[0]][vec[j]]);
            }
        vector<int> nvec;
        for (int k = 1; k < len; ++k)
            nvec.push_back(vec[k]);
        dfs(nvec, depth + 1, maxLen, sumLen);
    }
public:
    void solve() {
        clear();
        cin >> n;
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> map[i][j];
        vector<int> vec;
        for (int i = 1; i <= n; ++i)
            vec.push_back(i);
        dfs(vec, 1, 0, 0);
        printf("%d\n", count);
    }
};
int main() {
    Solver solver;
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        printf("Case #%d: ", i);
        solver.solve();
    }
    return 0;
}