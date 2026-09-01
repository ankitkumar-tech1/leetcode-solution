#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters in s
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check whether a palindrome is possible
        int odd = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Frequency of characters in the first half
        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) {
            halfCnt[i] = freq[i] / 2;
        }

        int m = n / 2;

        string targetLeft = target.substr(0, m);

        /*
         * ---------------------------------------------------------
         * STEP 1:
         * Try to construct targetLeft exactly.
         * If possible, this gives the smallest possible half
         * equal to targetLeft.
         * ---------------------------------------------------------
         */

        vector<int> rem = halfCnt;
        bool exactPossible = true;

        for (char c : targetLeft) {
            int x = c - 'a';

            if (rem[x] == 0) {
                exactPossible = false;
                break;
            }

            rem[x]--;
        }

        if (exactPossible) {
            string candidate = targetLeft;

            // Middle character
            if (n % 2)
                candidate += middle;

            // Mirror
            string rev = targetLeft;
            reverse(rev.begin(), rev.end());
            candidate += rev;

            // If exact half already gives a palindrome > target,
            // it is automatically the answer.
            if (candidate > target)
                return candidate;
        }

        /*
         * ---------------------------------------------------------
         * STEP 2:
         * Find the smallest half that is STRICTLY GREATER
         * than targetLeft.
         *
         * We keep targetLeft's prefix equal and increase the
         * rightmost possible position.
         * ---------------------------------------------------------
         */

        // prefixCnt[i][c] =
        // number of character c used by targetLeft[0 ... i-1]
        vector<array<int, 26>> prefix(m + 1);

        prefix[0].fill(0);

        for (int i = 0; i < m; i++) {
            prefix[i + 1] = prefix[i];
            prefix[i + 1][targetLeft[i] - 'a']++;
        }

        /*
         * Try the rightmost position first.
         *
         * Example:
         *
         * target = abcde
         *
         * Try:
         * abcd?
         * abc?e
         * ab?de
         * a?cde
         * ?bcde
         *
         * Rightmost successful change gives the smallest
         * possible greater permutation.
         */

        for (int pos = m - 1; pos >= 0; pos--) {

            // Characters remaining after using targetLeft[0..pos-1]
            vector<int> available = halfCnt;

            bool prefixPossible = true;

            for (int i = 0; i < pos; i++) {
                int x = targetLeft[i] - 'a';

                if (available[x] == 0) {
                    prefixPossible = false;
                    break;
                }

                available[x]--;
            }

            if (!prefixPossible)
                continue;

            int current = targetLeft[pos] - 'a';

            /*
             * At this position choose the smallest character
             * strictly greater than targetLeft[pos].
             */
            for (int c = current + 1; c < 26; c++) {

                if (available[c] == 0)
                    continue;

                string left = targetLeft.substr(0, pos);

                left += char('a' + c);

                available[c]--;

                // Fill the rest in ascending order.
                for (int x = 0; x < 26; x++) {
                    left.append(available[x], char('a' + x));
                }

                // Construct palindrome
                string answer = left;

                if (n % 2)
                    answer += middle;

                string rev = left;
                reverse(rev.begin(), rev.end());

                answer += rev;

                return answer;
            }
        }

        // No palindrome permutation > target
        return "";
    }
};