class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int allVisited = (1 << n) - 1;
        queue<pair<int, int>> q;
        vector<vector<int>> dist(n, vector<int>(1 << n, -1));

        for (int i = 0; i < n; i++) {
            q.push({i, 1 << i});
            dist[i][1 << i] = 0;
        }

        while (!q.empty()) {
            auto [node, mask] = q.front();
            q.pop();

            if (mask == allVisited) return dist[node][mask];

            for (int nei : graph[node]) {
                int nextMask = mask | (1 << nei);
                if (dist[nei][nextMask] == -1) {
                    dist[nei][nextMask] = dist[node][mask] + 1;
                    q.push({nei, nextMask});
                }
            }
        }
        return -1;
    }
};
