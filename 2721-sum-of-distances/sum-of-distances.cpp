class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }

        vector<long long> ans(n, 0);

        for (auto& [val, idx] : pos) {
            int k = idx.size();
            if (k == 1) continue; // only one occurrence → 0

            vector<long long> prefix(k, 0);
            prefix[0] = idx[0];
            for (int i = 1; i < k; i++) {
                prefix[i] = prefix[i-1] + idx[i];
            }

            for (int t = 0; t < k; t++) {
                long long left = (long long)t * idx[t] - (t > 0 ? prefix[t-1] : 0);
                long long right = (prefix[k-1] - prefix[t]) - (long long)(k - t - 1) * idx[t];
                ans[idx[t]] = left + right;
            }
        }

        return ans;
    }
};