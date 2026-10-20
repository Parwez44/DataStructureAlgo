
class Solution {
public:
    int m, n;
    int emptyCells = 0;
    int ans = 0;

    void dfs(vector<vector<int>>& grid, int r, int c, int remaining) {
        if (grid[r][c] == 2) {
            if (remaining == 1) {
                ans++;
            }
            return;
        }

        int original = grid[r][c];
        grid[r][c] = -1;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < m &&
                nc >= 0 && nc < n &&
                grid[nr][nc] != -1) {
                dfs(grid, nr, nc, remaining - 1);
            }
        }

        grid[r][c] = original;
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int sr = 0, sc = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != -1) {
                    emptyCells++;
                }

                if (grid[i][j] == 1) {
                    sr = i;
                    sc = j;
                }
            }
        }

        dfs(grid, sr, sc, emptyCells);

        return ans;
    }
};
