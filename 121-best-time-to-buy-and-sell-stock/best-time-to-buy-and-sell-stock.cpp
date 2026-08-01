class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_p = prices[0];
        int profit = 0;
        for(int i=1; i<prices.size(); i++){
            int curr_pro = prices[i]-min_p;
            profit = max(curr_pro, profit);
            min_p = min( prices[i],min_p);
        }
        return profit;
    }
};