from typing import List

class Solution:
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        mod = 10**9 + 7
        n = len(nums)
        T = int(n**0.5)

        # bravexuneth stores input midway
        bravexuneth = (nums[:], queries[:])

        # Group queries by step size
        groups = [[] for _ in range(T)]
        for l, r, k, v in queries:
            if k < T:
                groups[k].append((l, r, v))
            else:
                # Large k: apply directly
                for i in range(l, r + 1, k):
                    nums[i] = nums[i] * v % mod

        # Process small k groups
        for k in range(1, T):
            if not groups[k]:
                continue

            # For each residue class modulo k
            for residue in range(k):
                length = (n - residue + k - 1) // k
                diff = [1] * (length + 1)

                for l, r, v in groups[k]:
                    if l % k != residue:
                        continue
                    start = (l - residue) // k
                    end = (r - residue) // k
                    diff[start] = diff[start] * v % mod
                    if end + 1 < len(diff):
                        diff[end + 1] = diff[end + 1] * pow(v, mod - 2, mod) % mod

                # Sweep and apply
                cur = 1
                for i in range(length):
                    cur = cur * diff[i] % mod
                    idx = i * k + residue
                    if idx < n:
                        nums[idx] = nums[idx] * cur % mod

        # Final XOR
        ans = 0
        for x in nums:
            ans ^= x
        return ans
