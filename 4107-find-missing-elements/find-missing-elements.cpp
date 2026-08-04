class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(),nums.end());
       vector<int> ans ={};
        int n = nums[0];
        for(int i=0; i<nums.size();i++){
             if(nums[i]!=n){
                ans.push_back(n);
                i--;
             }
             n++;
        }
        return ans;
    }
};