class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int,int> m;
        
        for(int num : nums){
            m[num]++;
        }
        
        vector<pair<int,int>> p;
        
        for(auto x : m){
            p.push_back({x.second, x.first});
        }
        
        sort(p.begin(), p.end(), greater<pair<int,int>>());
        
        vector<int> result;
        
        for(int i = 0; i < k; i++){
            result.push_back(p[i].second);
        }
        
        return result;
    }
};