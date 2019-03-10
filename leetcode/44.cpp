#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool isMatch(string ss, string pp) {
        vector<char> s, p;
        s.push_back('z');
        p.push_back('z');
        int n = ss.length(), m = pp.length();
        for (int i = 0; i < n; ++i)
            s.push_back(ss[i]);
        for (int i = 0; i < n; ++i)
            p.push_back(pp[i]);
        ++n; 
        ++m;
        
        vector<vector<int> > dp;
        dp.resize(n);
        for (int i = 0; i < n; ++i)
            dp[i].resize(m);

        dp[0][0] = true;
        for (int i = 1; i < m; ++i) {
            if (p[i] == '*')
                dp[0][i] = true;
            else break;
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                if (p[j] == '*')
                    dp[i][j] = dp[i-1][j] | dp[i][j-1];
                else if (p[j] == '?')
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = dp[i-1][j-1] && (s[i]==p[j]);
            }
        }
        return dp[n-1][m-1];
    }
};
int main() {
    return 0;
}