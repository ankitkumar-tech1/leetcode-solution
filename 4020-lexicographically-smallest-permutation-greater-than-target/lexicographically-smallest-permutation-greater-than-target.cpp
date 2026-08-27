#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        string ans;
        vector<int> stack; // keep track of chosen chars

        for (int i = 0; i < n; i++) {
            int idx = target[i] - 'a';

            // 1. Try exact match
            if (freq[idx] > 0) {
                ans.push_back(target[i]);
                stack.push_back(idx);
                freq[idx]--;
                continue;
            }

            // 2. Try strictly greater
            for (int j = idx + 1; j < 26; j++) {
                if (freq[j] > 0) {
                    ans.push_back('a' + j);
                    freq[j]--;
                    // fill rest with smallest available
                    for (int k = 0; k < 26; k++) {
                        while (freq[k] > 0) {
                            ans.push_back('a' + k);
                            freq[k]--;
                        }
                    }
                    return ans;
                }
            }

            // 3. Backtrack
            while (!stack.empty()) {
                int prev = stack.back();
                stack.pop_back();
                freq[prev]++;
                ans.pop_back();

                for (int j = prev + 1; j < 26; j++) {
                    if (freq[j] > 0) {
                        ans.push_back('a' + j);
                        freq[j]--;
                        for (int k = 0; k < 26; k++) {
                            while (freq[k] > 0) {
                                ans.push_back('a' + k);
                                freq[k]--;
                            }
                        }
                        return ans;
                    }
                }
            }
            return ""; // no solution
        }

        // If we matched target fully, we still need strictly greater
        // Try to bump at the last possible position
        while (!stack.empty()) {
            int prev = stack.back();
            stack.pop_back();
            freq[prev]++;
            ans.pop_back();

            for (int j = prev + 1; j < 26; j++) {
                if (freq[j] > 0) {
                    ans.push_back('a' + j);
                    freq[j]--;
                    for (int k = 0; k < 26; k++) {
                        while (freq[k] > 0) {
                            ans.push_back('a' + k);
                            freq[k]--;
                        }
                    }
                    return ans;
                }
            }
        }
        return "";
    }
};
