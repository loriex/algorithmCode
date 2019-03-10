/*
    count porblem.
    POWERi = every subarray times a exp(i) array
    consider to count by every subarray:
    for a subarray Q:
    the contribution to POWERi is: Q[1] * 1^i + Q[2] * 2^i + ... + Q[q] * q^i
    the contribution to POWER  is: Q[1] * T[1] + Q[2]*T[2] + ... + Q[q]*T[q]
    T[i] = i^1 + i^2 + ... + i^K = (i^{k+1}-i) / (i-1)
    we can calc T on O(NlogK) (by pow function & inverse function of division)

    but there are many subarrays.
    so we refine our counting method

    for a subarray Q, we need to add a T[i] * Q[i] to result.
    T[i] is what we calced.

    according to ALL subarrays, Q[i] follow some interesting pattern(draw a picture you'll know it)
    add all coefficient of T[i], (the sum of all Q[i]), we get G[i]
    it's very fast to calc the sum of Q[i], by sum of prefix sum & sum of sum_of_prefix.

    the total time complexity is O(NlogK), well.. if we use multiplicative function & Linear sieve we can get O(N)
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define N 1000111
#define K 10011
#define MOD 1000000007
typedef long long LL;
LL pow(LL a, int b) {
    LL res = 1;
    while (b) {
        if (b & 1)
            res = (res * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}
LL mmod(LL a) {
    a %= MOD;
    if (a < 0)
        a += MOD;
    return a;
}
class Solver {
    LL A[N];
    LL sum[N], ssum[N];
    LL G[N];
    LL T[N];
    int n, k;
    void calcG() {
        //g[i] = (sum[n]-sum[i-1]) + (sum[n-1]-sum[i-1]) + ... + (sum[i]-sum[i-1])
        //     = ssum[n] - ssum[i-1] - (n-i+1) * sum[i-1]
        sum[0] = 0;
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i-1] + A[i];
        ssum[0] = 0;
        for (int i = 1; i <= n; ++i)
            ssum[i] = ssum[i-1] + sum[i];
        for (int i = 1; i <= n; ++i)
            G[i] = mmod(ssum[n] - ssum[i-1] - (n-i+1)*sum[i-1]%MOD);
    }
    void calcT() {
        //T[i] = i^1+i^2+i^3+...+i^k = (i^{k+1} - i) / (i-1)
        //except: T[1] = k
        T[1] = k;
        for (int i = 2; i <= n; ++i)
            T[i] = mmod(pow(i, k+1) - i) * pow(i-1, MOD-2) % MOD;
    }
public:
    void solve() {
        LL x1, y1, c, d, e1, e2, f, x, y;
        cin >> n >> k >> x1 >> y1 >> c >> d >> e1 >> e2 >> f;
        
        for (int i = 1; i <= n; ++i) {
            A[i] = (x1 + y1) % f;
            x = (c * x1 + d * y1 + e1) % f;
            y = (d * x1 + c * y1 + e2) % f;
            x1 = x;
            y1 = y;
        }
        calcG();
        calcT();
        LL res = 0;
        for (int i = 1; i <= n; ++i)
            res = res + G[i] * T[i] % MOD;
        res %= MOD;
        printf("%lld\n", res);
    }
}solver;
int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        printf("Case #%d: ", i);
        solver.solve();
    }
    return 0;
}