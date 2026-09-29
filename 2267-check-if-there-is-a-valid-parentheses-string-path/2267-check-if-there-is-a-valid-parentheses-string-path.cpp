class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int len = m + n - 1;

        if (len % 2 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        vector<vector<bool>> dp(n, vector<bool>(len + 1, false));
        dp[0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                vector<bool> cur(len + 1, false);
                int change = grid[i][j] == '(' ? 1 : -1;

                for (int bal = 0; bal <= len; bal++) {
                    if (i > 0 && dp[j][bal] && bal + change >= 0 && bal + change <= len)
                        cur[bal + change] = true;

                    if (j > 0 && dp[j - 1][bal] && bal + change >= 0 && bal + change <= len)
                        cur[bal + change] = true;
                }

                dp[j] = move(cur);
            }
        }

        return dp[n - 1][0];
    }
};