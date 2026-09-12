class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(a.begin(), a.end());

        vector<long long> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(starts.begin(), starts.end(), a[i][1]) - starts.begin();
        }

        vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));
        vector<vector<vector<int>>> ans(n + 1, vector<vector<int>>(5));

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {
                long long skip = dp[i + 1][k];
                long long take = a[i][2] + dp[nxt[i]][k - 1];

                if (take > skip) {
                    dp[i][k] = take;
                    ans[i][k] = ans[nxt[i]][k - 1];
                    ans[i][k].push_back(a[i][3]);
                }
                else if (skip > take) {
                    dp[i][k] = skip;
                    ans[i][k] = ans[i + 1][k];
                }
                else {
                    dp[i][k] = skip;

                    vector<int> x = ans[i + 1][k];
                    vector<int> y = ans[nxt[i]][k - 1];

                    y.push_back(a[i][3]);

                    sort(x.begin(), x.end());
                    sort(y.begin(), y.end());

                    if (y < x)
                        ans[i][k] = y;
                    else
                        ans[i][k] = x;
                }
            }
        }

        sort(ans[0][4].begin(), ans[0][4].end());

        return ans[0][4];
    }
};