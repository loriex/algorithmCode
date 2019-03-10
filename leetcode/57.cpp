/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        int num = intervals.size();
        for (int i = 0; i < num; ++i) {
            if (intervals[i].start > newInterval.end || intervals[i].end < newInterval.start)
                res.push_back(intervals[i]);
            else {
                newInterval.start = min(newInterval.start, intervals[i].start);
                newInterval.end = max(newInterval.end, intervals[i].end);
            }
        }
        res.push_back(newInterval);
        num = res.size();
        for (int i = num-1; i > 0; --i) {
            if (res[i].end < res[i-1].start)
                swap(res[i], res[i-1]);
        }
        return res;
    }
};
