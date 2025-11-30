const int MOD = 1e9+7;
vi knapsack_trick(int mx, vi weights) {
    vi frq(mx + 1);
    vi bulk;
    for(auto w : weights) frq[w]++;
    
    for(int w = 1; w <= mx; w++) { 
        if(!frq[w]) continue;
        int cnt = frq[w];
        
        // Reserve 3 singles 
        int singles = min(3ll, cnt);
        for(int k = 0; k < singles; k++) bulk.push_back(w); 
        
        cnt -= singles;
        
        // Binary Decomposition
        long long pw = 1;
        while(cnt >= pw) {
            bulk.push_back(w * pw);
            cnt -= pw;
            pw *= 2;
        }
        if(cnt > 0) bulk.push_back(w * cnt);
    }

    // 3. Build Base DP using COMPRESSED items
    vi dp(mx + 1, 0);
    dp[0] = 1;
    

    for(int val : bulk) { // (MX SQRT(MX)
        for(int j = mx; j >= val; j--) {
            dp[j] = (dp[j] + dp[j - val]);
            if(dp[j] >= MOD) dp[j] -= MOD;
        }
    }

    // 4. Removal and Query Phase
    for(int w = 1; w <= mx; w++) {
        if(frq[w] == 0) continue;
        
        // A. Remove ONE instance of 'w'
        for(int j = w; j <= mx; j++) {
            dp[j] = dp[j] - dp[j - w];
            if(dp[j] < 0) dp[j] += MOD;
        }

        // B. YOUR LOGIC HERE 
        // ...

        // C. Restore (Add 'w' back)
        for(int j = mx; j >= w; j--) {
            dp[j] = dp[j] + dp[j - w];
            if(dp[j] >= MOD) dp[j] -= MOD;
        }
    }
    
    return dp; 
}
