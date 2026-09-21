class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k), dp(k);

        for (int num : nums) {
            vector<long long> ndp(k);

            for (int r = 0; r < k; r++)
                ndp[(r * (num % k)) % k] += dp[r];

            ndp[num % k]++;
            dp = ndp;

            for (int r = 0; r < k; r++)
                ans[r] += dp[r];
        }

        return ans;
    }
};