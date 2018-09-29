#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> gg, huaji;
        int lent = t.length();
        for (int i = 0; i < lent; ++i) {
            gg[t[i]] = gg[t[i]] + 1;
            huaji[t[i]] = gg[t[i]];
        }
        int cnt = gg.size();
        int have = 0;
        int lens = s.length();
        int top = 0;
        int reslen = (int)1e10, res = -1;
        for (int i = 0; i < lens; ++i) {
            if (gg[s[i]] > 0) {
                huaji[s[i]] = huaji[s[i]] - 1;
                if (huaji[s[i]] == 0)
                    ++have;
            }
            if (have == cnt) {
                while (gg[s[top]] == 0 || (gg[s[top]] > 0 && huaji[s[top]] < 0)) {
                    if (gg[s[top]] > 0)
                        ++huaji[s[top]];
                    ++top;
                }
                //s[top~i].
                if (i-top+1 < reslen) {
                    reslen = i-top+1;
                    res = top;
                }
            }
        }
        if (res == -1) return "";
        return s.substr(res, reslen);
    }
};
int main() {
    Solution sol;
    int n;
    string s, t;
    cin >> s >> t;
    cout << sol.minWindow(s, t) << endl;
    return 0;
}