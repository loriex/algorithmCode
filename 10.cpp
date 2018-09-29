#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    struct Shit {
        char c;
        bool rep;
        Shit(char _c): c(_c), rep(false){}
        bool p(char g) {
            return c == g || c == '.';
        }
    };
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        vector<Shit> fk;
        int top = 0;
        for (int i = 0; i < m; ++i) {
            if (p[i] == '*')
                fk[top-1].rep = true;
            else {
                fk.push_back(Shit(p[i]));
                ++top;
            }
        }
        m = top;
        bool ok[n+1][m+1];
        for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            ok[i][j] = false;
        ok[0][0] = true;
        for (int j = 1; j <= m; ++j) {
            if (fk[j-1].rep == true)
                ok[0][j] = true;
            else 
                break;
        }
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (fk[j-1].rep == false) {
                if (fk[j-1].p(s[i-1]) && ok[i-1][j-1] == true)
                    ok[i][j] = true;
            }
            else {
                if (ok[i][j-1] == true) {
                    ok[i][j] = true;
                    continue;
                }
                for (int k = i; k >= 1; --k)
                    if (fk[j-1].p(s[k-1])) {
                        if (ok[k-1][j-1])
                            ok[i][j] = true;
                    }
                    else break;
            }
        }
        return ok[n][m];
    }
};
int main() {
    Solution s;
    string q = "ab";
    string p = ".*..";
    cout << (s.isMatch(q, p) ? "true" : "false") << endl;
    return 0;
}