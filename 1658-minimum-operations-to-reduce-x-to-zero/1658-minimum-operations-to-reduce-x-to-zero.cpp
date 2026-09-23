class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = total - x;

        int left = 0, sum = 0, maxLen = -1;

        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];

            while (left <= right && sum > target)
                sum -= nums[left++];

            if (sum == target)
                maxLen = max(maxLen, right - left + 1);
        }

        return maxLen == -1 ? -1 : nums.size() - maxLen;
    }
};