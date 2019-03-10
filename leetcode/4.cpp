#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool test(int mid, int fd, vector<int>& nums1, vector<int>& nums2) {
        int n = nums2.size();
        int sk = fd - mid;
        if (sk <= n) {
            if (sk > 0) {
                if (nums2[sk-1] <= nums1[mid-1])
                    return true;
                else return false;
            }
            return (sk==0);
        }
        return false;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //cout << "ss" << nums1[0] << endl;
        int m = nums1.size(), n = nums2.size();
        int fd = (m + n) / 2 + 1;
        int l = 1, r = min(m, fd);
        int ans = 0;
        while (r - l >= 2) {
            int mid = l + r >> 1;
            if (test(mid, fd, nums1, nums2))
                r = mid;
            else
                l = mid;
            //printf("%d %d\n", l, r);
        }
        for (int i = l; i <= r; ++i) {
            if (test(i, fd, nums1, nums2)) {
                ans = i;
                break;
            }
        }
        //printf("%d %d %d\n",ans, l, r);
        if (ans) {
            int sk = fd - ans;
            if (sk > 0 && nums1[ans-1] < nums2[sk-1])
                return findMedianSortedArrays(nums2, nums1);
            if (sk < n && nums1[ans-1] > nums2[sk])
                return findMedianSortedArrays(nums2, nums1);
            if ((m + n) % 2 == 1) {
                return nums1[ans-1];
            }
            else {
                int d1;
                if (ans > 1 && fd - ans > 0 && fd - ans <= n)
                    d1 = max(nums1[ans-2], nums2[fd - ans - 1]);
                else if (ans > 1)
                    d1 = nums1[ans-2];
                else
                    d1 = nums2[fd - ans - 1];
                //printf("%d\n",ans);
                return ((double)(nums1[ans-1]) + d1) / 2;
            }
        }
        return findMedianSortedArrays(nums2, nums1);
    }
};
int main() {
    Solution s;
    int s1[] = {1,2};
    int s2[] = {3,4};
    vector<int> n1(s1, s1+2);
    vector<int> n2(s2, s2+2);
    cout << s.findMedianSortedArrays(n1, n2) << endl;
    return 0;
}