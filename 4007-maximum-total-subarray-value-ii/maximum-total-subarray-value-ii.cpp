#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Build sparse tables for RMQ (max and min)
        int LOG = 32 - __builtin_clz(n);
        vector<vector<int>> stMax(LOG, vector<int>(n));
        vector<vector<int>> stMin(LOG, vector<int>(n));
        
        for (int i = 0; i < n; i++) {
            stMax[0][i] = nums[i];
            stMin[0][i] = nums[i];
        }
        
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                stMax[j][i] = max(stMax[j-1][i], stMax[j-1][i + (1 << (j-1))]);
                stMin[j][i] = min(stMin[j-1][i], stMin[j-1][i + (1 << (j-1))]);
            }
        }
        
        auto rangeMax = [&](int L, int R) {
            int j = 31 - __builtin_clz(R - L + 1);
            return max(stMax[j][L], stMax[j][R - (1 << j) + 1]);
        };
        
        auto rangeMin = [&](int L, int R) {
            int j = 31 - __builtin_clz(R - L + 1);
            return min(stMin[j][L], stMin[j][R - (1 << j) + 1]);
        };
        
        auto value = [&](int L, int R) {
            return (long long)rangeMax(L, R) - rangeMin(L, R);
        };
        
        // Max-heap: (value, l, r)
        using T = tuple<long long,int,int>;
        priority_queue<T> pq;
        
        for (int l = 0; l < n; l++) {
            pq.emplace(value(l, n-1), l, n-1);
        }
        
        long long ans = 0;
        for (int i = 0; i < k; i++) {
            auto [val, l, r] = pq.top(); pq.pop();
            ans += val;
            if (r > l) {
                pq.emplace(value(l, r-1), l, r-1);
            }
        }
        
        return ans;
    }
};
