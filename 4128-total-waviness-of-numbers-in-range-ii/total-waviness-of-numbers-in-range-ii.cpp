class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }

private:
    struct Node {
        long long count;
        long long sum;
    };

    string s;
    Node dp[20][2][2][11][11]; // prev1, prev2 ∈ [0..10], 10 = none
    bool vis[20][2][2][11][11];

    Node dfs(int pos, bool tight, bool started, int prev1, int prev2) {
        if (pos == s.size()) {
            return {started ? 1 : 0, 0};
        }
        if (vis[pos][tight][started][prev1][prev2])
            return dp[pos][tight][started][prev1][prev2];
        vis[pos][tight][started][prev1][prev2] = true;

        Node res = {0,0};
        int limit = tight ? (s[pos]-'0') : 9;
        for (int d=0; d<=limit; d++) {
            bool ntight = tight && (d==limit);
            bool nstarted = started || (d!=0);
            int np1 = prev1, np2 = prev2;
            long long add = 0;
            if (nstarted) {
                if (prev1!=10 && prev2!=10) {
                    if (prev1 > prev2 && prev1 > d) add++;
                    if (prev1 < prev2 && prev1 < d) add++;
                }
                np2 = prev1;
                np1 = d;
            }
            Node nxt = dfs(pos+1, ntight, nstarted, np1, np2);
            res.count += nxt.count;
            res.sum += nxt.sum + add * nxt.count;
        }
        return dp[pos][tight][started][prev1][prev2] = res;
    }

    long long solve(long long x) {
        if (x <= 0) return 0;
        s = to_string(x);
        memset(vis, 0, sizeof(vis));
        return dfs(0, true, false, 10, 10).sum;
    }
};
