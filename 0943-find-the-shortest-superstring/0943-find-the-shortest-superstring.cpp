class Solution {
public:
    int calc(string a, string b) {
        int maxOverlap = 0;

        for (int len = 1; len <= min(a.size(), b.size()); len++) {
            if (a.substr(a.size() - len) == b.substr(0, len))
                maxOverlap = len;
        }

        return b.size() - maxOverlap;
    }

    string shortestSuperstring(vector<string>& A) {
        int n = A.size();

        vector<vector<int>> graph(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j)
                    graph[i][j] = calc(A[i], A[j]);
            }
        }

        int totalMasks = 1 << n;
        const int INF = 1e9;

        vector<vector<int>> dp(totalMasks, vector<int>(n, INF));
        vector<vector<int>> path(totalMasks, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
            dp[1 << i][i] = A[i].size();

        for (int mask = 1; mask < totalMasks; mask++) {
            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j)))
                    continue;

                int prev = mask ^ (1 << j);

                if (prev == 0)
                    continue;

                for (int k = 0; k < n; k++) {
                    if (!(prev & (1 << k)))
                        continue;

                    if (dp[prev][k] + graph[k][j] < dp[mask][j]) {
                        dp[mask][j] = dp[prev][k] + graph[k][j];
                        path[mask][j] = k;
                    }
                }
            }
        }

        int fullMask = totalMasks - 1;
        int last = 0;

        for (int i = 1; i < n; i++) {
            if (dp[fullMask][i] < dp[fullMask][last])
                last = i;
        }

        vector<int> order;
        int mask = fullMask;

        while (last != -1) {
            order.push_back(last);
            int prev = path[mask][last];
            mask ^= (1 << last);
            last = prev;
        }

        reverse(order.begin(), order.end());

        string ans = A[order[0]];

        for (int i = 1; i < n; i++) {
            int prev = order[i - 1];
            int curr = order[i];

            int overlap = A[curr].size() - graph[prev][curr];

            ans += A[curr].substr(overlap);
        }

        return ans;
    }
};