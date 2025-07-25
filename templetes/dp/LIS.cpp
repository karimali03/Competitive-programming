
int lengthOfLIS(vector<int> & v) { // O( n *  log(n) )

        int n = v.size();
        
        vector<int>bs(n+1,INT_MAX);
        
        for(int i = 0 ;i < n ;i++){
        
            int x = lower_bound(bs.begin(),bs.begin()+i+1,v[i]) - bs.begin();
            
            bs[x] = v[i];
        }

        return lower_bound(bs.begin(),bs.end(),INT_MAX)-bs.begin();
}


int lengthOfLIS(vector<int>& v) {   // O(n^2)

        v.insert(v.begin(),INT_MIN);
        
        int dp[2501];
        
        memset(dp,-1,sizeof(dp));
        
        int n = v.size();
        
        dp[n-1] = 1;

        for(int i = n-1 ;i >=0;i--){
        
            int & ret = dp[i];
            
            ret = 1;
            
            for(int j = i+1 ; j < n ;j++){
            
                if(v[i] < v[j]) ret = max(ret,1+dp[j]);
            
            }
        
        }

        return dp[0]-1;
}