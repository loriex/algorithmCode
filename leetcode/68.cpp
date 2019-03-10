#include <string>
#include <vector>
using namespace std;
class Line {
private:
    vector<string> words;
    int wordslen, wordscnt, maxlen;
public:
    void clear() {
        words.clear();
        wordslen = wordscnt = 0;
    }
    void setLen(int len) {
        maxlen = len;
    }
    bool push(string word) {
        if (wordslen + word.length() + wordscnt > maxlen) return false;
        wordslen += word.length();
        ++wordscnt;
        words.push_back(string(word));
        return true;
    }
    string print(bool isLastLine) {
        int spacenum, addnum;
        if (isLastLine || words.size() == 1) {
            spacenum = 1;
            addnum = 0;
        }
        else {
            int spacecnt = maxlen - wordslen;
            spacenum = spacecnt / (wordscnt-1);
            addnum = spacecnt % (wordscnt-1);
        }
        string res;
        for (int i = 0; i < words.size(); ++i) {
            res += words[i];
            if (i < (words.size() - 1)) {
                int cnt = spacenum + (i < addnum ? 1 : 0);
                while (cnt--)
                    res += " ";
            }
        }
        while (res.length() < maxlen) res += " ";
        return res;
    }
};
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int num = words.size();

        vector<string> res;

        Line line;
        line.setLen(maxWidth);
        line.clear();

        for (int i = 0; i < num; ++i) {
            if (line.push(words[i]) == false) {
                res.push_back(line.print(false));
                line.clear();
                --i;
                continue;
            }
        }
        res.push_back(line.print(true));
        return res;
    }
};