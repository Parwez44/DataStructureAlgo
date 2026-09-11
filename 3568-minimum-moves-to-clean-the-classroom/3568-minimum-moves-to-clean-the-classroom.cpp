class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc, cnt = 0;
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }

        int fullMask = (1 << cnt) - 1;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(1 << cnt, -1))
        );

        queue<array<int, 4>> q;

        q.push({sr, sc, 0, energy});
        best[sr][sc][0] = energy;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X' || e == 0)
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (classroom[nr][nc] == 'L')
                        nmask |= (1 << id[nr][nc]);

                    if (classroom[nr][nc] == 'R')
                        ne = energy;

                    if (ne > best[nr][nc][nmask]) {
                        best[nr][nc][nmask] = ne;
                        q.push({nr, nc, nmask, ne});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};