class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp;
        int n = nums.size();

        for (int val : nums) {
            mp[val]++;

            if (mp[val] > n / 2) {
                return val;
            }
        }

        return -1;
    }
};