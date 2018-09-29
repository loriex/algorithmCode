#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        int dep = 0;
        map<int, int> minl;
        minl[-1] = -1;
        dep = -1;
        int ans = 0;
        for (int i = 0; i < len; ++i) {
            if (s[i] == '(') {
                ++dep;
                minl[dep] = i;
            }
            else {
                minl.erase(dep);
                --dep;
                if (minl.find(dep) != minl.end())
                    ans = max(ans, i - minl[dep]);
                else
                    minl[dep] = i;
            }
        }
        return ans;
    }
};
int main() {
    Solution sol;
    string s;
    cin >> s;
    cout << sol.longestValidParentheses(s) << endl;
    return 0;
}
