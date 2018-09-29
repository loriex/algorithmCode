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
class AhoCorasickAutomaton {
private:
    struct Node {
        int tag;
        int fail;
        int dep;
        int fa;
        int next[26];
        Node() {
            tag = 0;
            fail = 0;
            dep = 0;
            fa = 0;
            memset(next, 0, sizeof(next));
        }
    };
    vector<Node> nodes;
    int top;
public:
    AhoCorasickAutomaton() {
        nodes.resize(2);
        top = 1;
        nodes[1].fail = 1;
        nodes[1].fa = 1;
    }
    //tag >= 1
    void addWord(string word, int tag) {
        int id = 1;
        for (int i = 0; i < word.length(); ++i) {
            if (nodes[id].next[word[i]-'a']) {
                id = nodes[id].next[word[i]-'a'];
            }
            else {
                nodes.push_back(Node());
                ++top;
                nodes[top].dep = nodes[id].dep + 1;
                nodes[top].fa = id;
                id = nodes[id].next[word[i]-'a'] = top;
            }
        }
        nodes[id].tag = tag;
    }
    void buildFailTree() {
        queue<int> que;
        for (int i = 0; i < 26; ++i) {
            if (nodes[1].next[i] == 0)
                nodes[1].next[i] = 1;
            else {
                nodes[nodes[1].next[i]].fail = 1;
                que.push(nodes[1].next[i]);
            }
        }
        while (!que.empty()){
            int i = que.front();
            que.pop();
            int fail = nodes[i].fail;
            for (int j = 0; j < 26; ++j) {
                if (nodes[i].next[j] == 0) {
                    nodes[i].next[j] = nodes[fail].next[j];
                }
                else {
                    nodes[nodes[i].next[j]].fail = nodes[fail].next[j];
                    que.push(nodes[i].next[j]);
                }
            }
        }
    }
    void make(vector<string> &words) {
        for (int i = 0; i < words.size(); ++i)
            addWord(words[i], i+1);
        buildFailTree();
    }
    vector<int> match(string s) {
        vector<int> res;
        int id = 1;
        for (int i = 0; i < s.length(); ++i) {
            id = nodes[id].next[s[i]-'a'];
            //printf("%d",id);
            res.push_back(nodes[id].tag);
        }
        //printf("\n");
        return res;
    }
};
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (s.length() == 0 || words.size() == 0 || words[0].length() == 0) return vector<int>();
        
        map<string, int> gg;
        for (int i = 0; i < words.size(); ++i)
            gg[words[i]] = gg[words[i]] + 1;

        AhoCorasickAutomaton sol;
        vector<string> strings;
        for (auto i : gg)
            strings.push_back(i.first);
        sol.make(strings);

        vector<int> tag = sol.match(s);
        // for (int i = 0; i < tag.size(); ++i) {
        //     printf("%d", tag[i]);
        // }
        // cout << endl << s << endl;
        vector<int> CNT;
        CNT.push_back(0);
        for (auto i : gg) {
            CNT.push_back(i.second);
        }

        int k = words[0].length(), n = s.length();
        int num = words.size();
        vector<int> res;
        for (int i = 0; i < k; ++i) {
            // printf("Solving i=%d\n",i);
            vector<int> cnt(CNT);
            int notzero = CNT.size() - 1;
            for (int j = i; j < n; j += k) {
                // printf("%d tag%d ", j, tag[j]);
                if (tag[j]) {
                    cnt[tag[j]]--;
                    if (cnt[tag[j]] == 0)
                        --notzero;
                    if (cnt[tag[j]] == -1)
                        ++notzero;
                }
                if (j-k*num>=0 && tag[j-k*num]) {
                    cnt[tag[j-k*num]]++;
                    if (cnt[tag[j-k*num]] == 0)
                        --notzero;
                    if (cnt[tag[j-k*num]] == 1)
                        ++notzero;
                }
                if (notzero == 0) {
                    res.push_back(j-k*num + 1);
                }
                // printf("  notzero%d\n", notzero);
            }
        }
        return res;
    }
};
int main() {
    Solution sol;
    int n;
    string s, t;
    vector<string> words;
    cin >> s >> n;
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        words.push_back(t);
    }
    vector<int> res = sol.findSubstring(s, words);
    for (int i = 0; i < res.size(); ++i)
        printf("%d ", res[i]);
    return 0;
}