class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        int lo = 1, hi = 0;
        for (auto &e : edges) hi = max(hi, e[2] * 2);
        int ans = -1;

        auto can = [&](int mid) {
            DSU dsu(n);
            int used = 0, upgrades = 0;

            // must edges
            for (auto &e : edges) {
                if (e[3] == 1) {
                    if (e[2] < mid) return false; // too weak
                    if (!dsu.unite(e[0], e[1])) return false; // cycle
                    used++;
                }
            }

            // optional edges
            vector<array<int,4>> opt; 
            // store {strength, u, v, needsUpgrade}
            for (auto &e : edges) {
                if (e[3] == 0) {
                    if (e[2] >= mid) opt.push_back({e[2], e[0], e[1], 0});
                    else if (e[2]*2 >= mid) opt.push_back({e[2], e[0], e[1], 1});
                }
            }

            // sort stronger first (so we prefer high strength edges)
            sort(opt.begin(), opt.end(), [&](auto &a, auto &b){
                return a[0] > b[0];
            });

            for (auto &e : opt) {
                if (used == n-1) break;
                if (e[3] == 1 && upgrades == k) continue; // no upgrades left
                if (dsu.unite(e[1], e[2])) {
                    used++;
                    if (e[3] == 1) upgrades++;
                }
            }

            return used == n-1;
        };

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
