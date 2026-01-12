class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        queue<int> que;
        int time = 0;
        int val;

        for (int i = 0; i < tickets.size(); i++) {
            que.push(i);
        }

        while (tickets[k] > 0) {
            val = que.front();
            que.pop();

            tickets[val]--;
            time++;

            if (tickets[val] == 0 && val == k) {
                return time;
            }

            if (tickets[val] > 0) {
                que.push(val);
            }
        }

        return time;
    }
};
