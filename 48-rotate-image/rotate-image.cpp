class Solution {
public:
    void rotate(vector<vector<int>>& A) {
        int N = A.size();
        for (int i = 0; i < N / 2; ++i) {
            for (int j = i; j < N - i - 1; ++j) {
                int tmp = A[i][j];
                A[i][j] = A[N - j - 1][i];
                A[N - j - 1][i] = A[N - i - 1][N - j - 1];
                A[N - i - 1][N - j - 1] = A[j][N - i - 1];
                A[j][N - i - 1] = tmp;
            }
        }
    }
};