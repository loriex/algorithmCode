class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int cnt = 0, len = nums.size(), ed = nums.size();
        for (int i = 0; i < ed; ++i) {
            nums[i] -= 1;
        }
        for (int i = 0; i < len; ++i) {
            while (nums[i] != i) {
                int j = nums[i];
                if (j < 0 || j >= len || nums[j] == j) break;
                swap(nums[i], nums[j]);
            }
        }
        for (int i = 0; i < len; ++i) {
            if (nums[i] != i) return i + 1;
        }
        return len + 1;
    }
};