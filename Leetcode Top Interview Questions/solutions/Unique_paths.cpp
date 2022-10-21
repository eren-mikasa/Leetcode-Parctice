class Solution {
public:
    int solve(int i, int j, vector<vector<int>> &dp, int& m, int& n) {
        //base cases
        if(i == m-1 || j == n-1) return 1;
        if(dp[i][j] != -1) return dp[i][j];
        
        int right = solve(i,j+1,dp,m,n);
        int down = solve(i+1,j,dp,m,n);
        
        return dp[i][j] = right+down;
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m , vector<int>(n , -1));
        return solve(0, 0, dp, m, n);
    }
};
