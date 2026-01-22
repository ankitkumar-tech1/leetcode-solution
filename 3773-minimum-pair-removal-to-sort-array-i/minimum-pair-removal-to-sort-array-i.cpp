class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
    int operations = 0;

    // Helper lambda to check non-decreasing
    auto isNonDecreasing = [&](vector<int>& a) {
        for (int i = 1; i < a.size(); i++) {
            if (a[i] < a[i - 1]) return false;
        }
        return true;
    };

    while (!isNonDecreasing(nums)) {
        int minSum = INT_MAX;
        int idx = 0;

        // Find leftmost adjacent pair with minimum sum
        for (int i = 0; i < nums.size() - 1; i++) {
            int sum = nums[i] + nums[i + 1];
            if (sum < minSum) {
                minSum = sum;
                idx = i;
            }
        }

        // Replace the pair with their sum
        nums[idx] = nums[idx] + nums[idx + 1];
        nums.erase(nums.begin() + idx + 1);

        operations++;
    }

    return operations;
}

};