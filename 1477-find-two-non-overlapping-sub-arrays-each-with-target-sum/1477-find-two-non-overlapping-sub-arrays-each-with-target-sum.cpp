class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> best(n, INT_MAX);
        unordered_map<int, int> mp;
        mp[0] = -1;

        int sum = 0, ans = INT_MAX, len = INT_MAX;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (mp.count(sum - target)) {
                int j = mp[sum - target];
                len = i - j;

                if (j >= 0 && best[j] != INT_MAX)
                    ans = min(ans, len + best[j]);
            }

            if (len != INT_MAX)
                best[i] = min(i > 0 ? best[i - 1] : INT_MAX, len);
            else if (i > 0)
                best[i] = best[i - 1];

            mp[sum] = i;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};