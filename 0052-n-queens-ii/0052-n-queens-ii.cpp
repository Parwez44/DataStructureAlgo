class Solution {
public:
    int ans = 0;

    void backtrack(int row, int n, vector<bool>& cols,
                   vector<bool>& diag1, vector<bool>& diag2) {
        if (row == n) {
            ans++;
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row - col + n - 1] || diag2[row + col])
                continue;

            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;

            backtrack(row + 1, n, cols, diag1, diag2);

            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
        }
    }

    int totalNQueens(int n) {
        ans = 0;
        vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);

        backtrack(0, n, cols, diag1, diag2);

        return ans;
    }
};