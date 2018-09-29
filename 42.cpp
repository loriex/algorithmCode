
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> lm, rm;
        int ma = 0;
        for (int i = 0; i < n; ++i) {
            ma = max(ma, height[i]);
            lm.push_back(ma);
        }
        ma = 0;
        for (int i = n-1; i >= 0; --i) {
            ma = max(ma, height[i]);
            rm.push_back(ma);
        }
        int res = 0;
        for (int i = 0; i < n; ++i)
            res += max(lm[i], rm[i]) - height[i];
        return res;
    }
};