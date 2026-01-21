class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
    vector<int> ans;

    for (int n : nums) {
        if ((n & 1) == 0) {
            ans.push_back(-1); // even → impossible
        } else {
            int temp = n;
            int trailingOnes = 0;

            // count trailing 1s
            while (temp & 1) {
                trailingOnes++;
                temp >>= 1;
            }

            ans.push_back(n - (1 << (trailingOnes - 1)));
        }
    }

    return ans;
}


};