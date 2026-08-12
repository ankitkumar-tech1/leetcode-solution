class Solution {
public:
    vector<vector<int>> result;

    void permutation(vector<int>& nums, int i, int size) {
        if (i == size) {
            result.push_back(nums);
            return;
        }
        for (int j = i; j <= size; j++) {
            swap(nums[i], nums[j]);
            permutation(nums, i + 1, size);
            swap(nums[i], nums[j]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        permutation(nums, 0, nums.size() - 1);
        return result;
    }
};
