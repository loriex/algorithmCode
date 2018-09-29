#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Heap {
private:
public:
    int SMAX = -2147483647;
    int size;
    vector<int> p; //position of list[i]
    vector<int> v; //heap-value[]
    vector<int> s; //subscript of h[i]
    void Swap(int a, int b) {
        int sa = s[a], sb = s[b];
        swap(p[sa], p[sb]);
        swap(s[a], s[b]);
        swap(v[a], v[b]);
    }
    int Down(int sit) {
        int l = sit << 1, r = l + 1;
        if (l > size) return sit;
        if (r > size) {
            if (v[sit] > v[l]) {
                Swap(sit, l);
                return l;
            }
            return sit;
        }
        else {
            if (v[sit] > v[l] || v[sit] > v[r]) {
                int cho = v[l] <= v[r] ? l : r;
                Swap(sit, cho);
                return cho;
            }
            return sit;
        }
    }
    void null(int siz) {
        size = siz;
        p.resize(size + 1);
        v.resize(size + 1);
        s.resize(size + 1);
        for (int i = 1; i <= size; ++i) {
            p[i] = i;
            v[i] = SMAX;
            s[i] = i;
        }
    }
    void print() {
        for (int i = 1; i <= size; ++i) {
            printf("[%d,%d]",v[i],s[i]);
        }
        printf("\n");
    }
    //pair<int,int>(subscript, value)
    pair<int,int> top() {
        return pair<int,int>(s[1], v[1]);
    }
    void Just(int sit0) {
        while (1) {
            int sit1 = Down(sit0);
            if (sit1 == sit0)
                break;
            sit0 = sit1;
        }
    }
    //change the value of heap-top
    void change(int val) {
        int sit0 = 1;
        v[sit0] = val;
        Just(sit0);
    }
};
class Solution {
private:
    int MAX = 2147483647;
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> list;
        int k = lists.size();
        for (int i = 0; i < k; ++i) {
            if (lists[i] != nullptr && lists[i] != 0)
                list.push_back(lists[i]);
        }
        k = list.size();
        //cout << k << endl;
        ListNode *res = NULL, *end = NULL;
        Heap sol;
        sol.null(k);
        int rest = k;
        for (int i = 0; i < k; ++i) {
            sol.v[i+1] = list[i]->val;
            list[i] = list[i]->next;
        }
        for (int i = k; i >= 1; --i)
            sol.Just(i);
        while (rest) {
            //sol.print();
            pair<int,int> g = sol.top();
            int sub = g.first - 1, val = g.second;
            //printf("get %d\n", val);
            if (list[sub] == NULL) {
                rest--;
                sol.change(MAX);
            }
            else {
                sol.change(list[sub]->val);
                list[sub] = list[sub]->next;
            }
            if (end == NULL)
                res = end = new ListNode(val);
            else
                end = end->next = new ListNode(val);
        }
        return res;
    }
};
ListNode* mklist() {
    int k;
    cin >> k;
    if (k == 0) return NULL;
    ListNode *res, *end;
    res = end = new ListNode(0);
    int val;
    for (int i = 1; i <= k; ++i) {
        cin >> val;
        end = end->next = new ListNode(val);
    }
    end = res->next;
    delete res;
    return end;
}
void print(ListNode *p) {
    while (p != NULL) {
        printf("%d->", p->val);
        p = p->next;
    }
    printf("\n");
}
int main() {
    Solution s;
    int n;
    cin >> n;
    vector<ListNode*> k;
    for (int i = 0; i < n; ++i)
        k.push_back(mklist());
    ListNode *res = s.mergeKLists(k);
    print(res);
    return 0;
}