#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to fill the DP table
vector<vector<int>> LCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Create a 2D array to store lengths of LCS
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill dp array using bottom-up approach
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp;
}

// Function to reconstruct the LCS from the DP table
string reconstructLCS(const string& s1, const string& s2, const vector<vector<int>>& dp) {
    int i = s1.length();
    int j = s2.length();
    string lcs_str;

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_str.push_back(s1[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    // The lcs_str will be in reverse order, reverse it to get the correct LCS
    reverse(lcs_str.begin(), lcs_str.end());

    return lcs_str;
}
