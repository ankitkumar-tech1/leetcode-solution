#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        // Put all numbers into a set for O(1) lookup
        unordered_set<int> s(nums.begin(), nums.end());

        // Start from k, check each multiple
        int multiple = k;
        while (true) {
            if (s.find(multiple) == s.end()) {
                return multiple; // first missing multiple
            }
            multiple += k;
        }
        // unreachable
        return -1;
    }
};
