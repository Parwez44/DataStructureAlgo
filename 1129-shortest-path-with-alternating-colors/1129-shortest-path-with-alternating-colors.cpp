class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto& e : redEdges)
            adj[e[0]].push_back({e[1], 0});

        for (auto& e : blueEdges)
            adj[e[0]].push_back({e[1], 1});

        vector<vector<int>> dist(n, vector<int>(2, INT_MAX));
        queue<pair<int, int>> q;

        dist[0][0] = dist[0][1] = 0;
        q.push({0, 0});
        q.push({0, 1});

        while (!q.empty()) {
            auto [node, color] = q.front();
            q.pop();

            for (auto [next, edgeColor] : adj[node]) {
                if (edgeColor == color || dist[next][edgeColor] != INT_MAX)
                    continue;

                dist[next][edgeColor] = dist[node][color] + 1;
                q.push({next, edgeColor});
            }
        }

        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int d = min(dist[i][0], dist[i][1]);
            ans[i] = d == INT_MAX ? -1 : d;
        }

        return ans;
    }
};