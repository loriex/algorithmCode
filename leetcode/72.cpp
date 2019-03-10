class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        if (n == 0 || m == 0) return max(n, m);
        int dp[n][m];
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dp[i][j] = 0x7fffffff;
        dp[0][0] = word1[0] != word2[0];
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (i || j) {
                int rc = min((j==0?(i+1):dp[i][j-1]) + 1, (i==0?(j+1):dp[i-1][j]) + 1);
                rc = min(rc, ((i&&j)?dp[i-1][j-1]:(max(i,j)))+(word1[i]==word2[j]?0:1));
                dp[i][j] = rc;
            }
        return dp[n-1][m-1];
    }
};