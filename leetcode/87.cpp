#include <string>
using namespace std;
class Cnt {
    int cnt[128];
    int zero;
public:
    Cnt() {
        zero = 128;
        memset(cnt, 0, sizeof(cnt));
    }
    void add(char c) {
        ++cnt[c];
        if (cnt[c] == 1) --zero;
        if (cnt[c] == 0) ++zero;
    }
    void del(char c) {
        --cnt[c];
        if (cnt[c] == -1) --zero;
        if (cnt[c] == 0) ++zero;
    }
    bool emp() {
        return zero == 128;
    }
};
class Solution {
public:
    bool isScramble(string s1, string s2) {
        //cout << s1 << " [] " << s2 << endl;
        int len = s1.length();
        if (len != s2.length()) return false;
        if (len == 1) {
            return s1[0] == s2[0];
        }
        Cnt cnt;
        for (int i = 0; i < len; ++i) {
            cnt.add(s1[i]);
            cnt.del(s2[i]);
            if (i == len - 1) break;
            if (cnt.emp()) {
                if (isScramble(s1.substr(0, i+1), s2.substr(0,i+1)) 
                && isScramble(s1.substr(i+1), s2.substr(i+1)))
                    return true;
            }
        }
        for (int i = 0; i < len - 1; ++i) {
            cnt.add(s1[i]);
            cnt.del(s2[len-1-i]);
            if (cnt.emp()) {
                if (isScramble(s1.substr(0, i+1), s2.substr(len-1-i)) 
                && isScramble(s1.substr(i+1), s2.substr(0,len -1-i)))
                    return true;
            }
        }
        return false;
    }
};