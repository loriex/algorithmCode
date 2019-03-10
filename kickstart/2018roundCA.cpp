#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define N 1024
class Solver {
    //answer array
    int dist[N];

    //adjacency list
    struct Edge {
        int to, last;
    }edges[N<<1];
    int last[N];
    int top;
    void addEdge(int from, int to) {
        edges[++top].to = to;
        edges[top].last = last[from];
        last[from] = top;
    }

    int n;

    void clear() {
        memset(dist, 0, sizeof(dist));
        memset(last, 0, sizeof(last));
        n = top = 0;
    }
public:
    void solve() {
        clear();
        cin >> n;
        int u, v;
        for (int i = 1; i <= n; ++i) {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
            //bidirectional edge
        }
        //first, find the circle.
        //use the algorithm that sort a DAG.
        vector<int> degree(n+1);
        for (int i = 1; i <= n; ++i) 
            degree[i] = 0;
        for (int i = 1; i <= top; ++i)
            ++degree[edges[i].to];
        queue<int> que;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] == 1) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int a = que.front(); que.pop();
            for (int i = last[a]; i; i = edges[i].last) {
                int to = edges[i].to;
                if (degree[to] > 1) {
                    degree[to]--;
                    if (degree[to] == 1)
                        que.push(to);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (degree[i] > 1) {
                dist[i] = 0;
                que.push(i);
            }
            else
                dist[i] = n;
        }
        while (!que.empty()) {
            int a = que.front(); que.pop();
            for (int i = last[a]; i; i = edges[i].last) {
                int to = edges[i].to;
                if (dist[to] == n) {
                    dist[to] = dist[a] + 1;
                    que.push(to);
                }
            }
        }
        for (int i = 1; i <= n; ++i)
            printf("%d ", dist[i]);
        printf("\n");
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