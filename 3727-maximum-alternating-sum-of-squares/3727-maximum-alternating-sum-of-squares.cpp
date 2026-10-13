class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        vector<long long> squares;
        for (int i = 0; i < n; i++) {
            squares.push_back((long long)nums[i] * nums[i]);
        }

        sort(squares.begin(), squares.end());

        int minusCount = n / 2;

        long long minusSum = 0;
        for (int i = 0; i < minusCount; i++) {
            minusSum += squares[i];
        }

        long long plusSum = 0;
        for (int i = minusCount; i < n; i++) {
            plusSum += squares[i];
        }

        return plusSum - minusSum;
    }
};