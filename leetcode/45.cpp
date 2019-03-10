class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();

        vector<int> numm;
        numm.resize(n);
        for (int i = 0; i < n; ++i)
            numm[i] = nums[i] + i;

        int cnt = 0, l = 0, r = 0;
        deque<pair<int,int>> shit;
        shit.push_back(pair<int,int>(0, numm[0]));

        while (r < n - 1) {
            while (numm[l] < r) {
                if (shit.front().first == l) shit.pop_front();
                ++l;
            }
            int h1 = shit.front().first, h2 = shit.front().second;
            while (r < h2) {
                ++r;
                while ((!shit.empty()) && shit.back().second <= numm[r]) {
                    shit.pop_back();
                }
                shit.push_back(pair<int,int>(r, numm[r]));
            }
            ++l;
            ++cnt;
        }
        return cnt;
    }
};