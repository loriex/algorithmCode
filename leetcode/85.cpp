#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (n <= 1) return n ? heights[0] : 0;

            vector<pair<int,int> > high;
            vector<int> lrea, rrea;
            high.resize(n);
            lrea.resize(n);
            rrea.resize(n);

            int rear;
            
            rear = 0;
            high[0] = pair<int,int>(0,heights[0]);
            lrea[0] = 0;
            for (int i = 1; i < n; ++i) {
                int cnt = i;
                while (rear >= 0 && high[rear].second >= heights[i]) {
                    cnt = high[rear].first;
                    --rear;
                }
                high[++rear] = pair<int,int>(cnt,heights[i]);
                lrea[i] = cnt;
            }

            rear = 0;
            high[0] = pair<int,int>(n-1, heights[n-1]);
            rrea[n-1] = n-1;
            for (int i = n-2; i >= 0; --i) {
                int cnt = i;
                while (rear >= 0 && high[rear].second >= heights[i]) {
                    cnt = high[rear].first;
                    --rear;
                }
                high[++rear] = pair<int,int>(cnt,heights[i]);
                rrea[i] = cnt;
            }

        int res = 0;
        for (int i = 0; i < n; ++i)
            res = max(res, heights[i] * (rrea[i]-lrea[i]+1));
        return res;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int n, m;
        n = matrix.size();
        if (n == 0) return 0;
        m = matrix[0].size();
        if (m == 0) return 0;
        vector<vector<int> > ll;
        ll.resize(n);
        for (int i = 0; i < n; ++i)
            ll[i].resize(m);
        for (int i = 0; i < n; ++i) {
            ll[i][m-1] = matrix[i][m-1] - '0';
            for (int j = m-2; j >= 0; --j) {
                ll[i][j] = matrix[i][j] == '1' ? (1 + ll[i][j+1]) : 0;
            }
        }
        int res = 0;
        vector<int> heights;
        heights.resize(n);
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i)
                heights[i] = ll[i][j];
            res = max(res, largestRectangleArea(heights));
        }
        return res;
    }
};