class Solution {
public:
    static constexpr int MOD = 1e9 + 7;

    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n + 1);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // BFS to compute depth
        vector<int> depth(n + 1, -1);
        queue<int> q;
        depth[1] = 0;
        q.push(1);

        int maxDepth = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    maxDepth = max(maxDepth, depth[v]);
                    q.push(v);
                }
            }
        }

        // Answer = 2^(maxDepth - 1) mod MOD
        return modPow(2, maxDepth - 1, MOD);
    }

private:
    long long modPow(long long base, long long exp, long long mod) {
        long long res = 1;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }
};
