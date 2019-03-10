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
class Solution {
public:
    int cnt(ListNode *p) {
        int res = 0;
        while (p != NULL) {
            ++res;
            p = p->next;
        }
        return res;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;

        int len = cnt(head);
        ListNode *mh = new ListNode(0), *sh = mh;
        mh->next = head;
        while (len >= k) {
            //reverse sh[1] ~ sh[k]
            //sh[k+1] != NULL
            ListNode *sh0 = sh, *shkt = NULL, *sh1 = sh0->next, *prev = sh0, *now = prev->next, *next = now->next;
            for (int i = 1; i <= k; ++i) {
                now->next = prev;
                if (i == k) {
                    shkt = next;
                }
                else {
                    prev = now;
                    now = next;
                    next = next->next;
                }
            }
            sh0->next = now;
            sh1->next = shkt;
            sh = sh1;
            len -= k;
        }
        sh = mh->next;
        delete mh;
        return sh;
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
    int kk;
    cin >> kk;
    vector<ListNode*> k;
    ListNode *res = s.reverseKGroup(mklist(), kk);
    print(res);
    return 0;
}