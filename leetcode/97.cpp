#include <string>
using namespace std;
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int l1, l2, l3;
        l1 = s1.length();
        l2 = s2.length();
        l3 = s3.length();
        if (l1 + l2 != l3) return false;
        if (l1 == 0) return s2 == s3;
        if (l2 == 0) return s1 == s3;
        bool dp[l1+1][l2+1];
        dp[0][0] = true;
        for (int i = 0; i < l1; ++i)
            dp[i+1][0] = dp[i][0] && (s1[i] == s3[i]);
        for (int i = 0; i < l2; ++i)
            dp[0][i+1] = dp[0][i] && (s2[i] == s3[i]);
        
        for (int i = 0; i < l1; ++i)
        for (int j = 0; j < l2; ++j)
            if (s1[i] == s3[i+j+1] && dp[i][j+1])
                dp[i+1][j+1] = true;
            else if (s2[j] == s3[i+j+1] && dp[i+1][j])
                dp[i+1][j+1] = true;
            else dp[i+1][j+1] = false;
        return dp[l1][l2];
    }
};