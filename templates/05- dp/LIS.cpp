vi calcLIS(vector<int> & v) { // O( n *  log(n) )
        int n = v.size();
        vector<int>bs(n+1,INT_MAX);
        vii idx(n+1);
        for(int i = 0 ;i < n ;i++){
            int x = lower_bound(bs.begin(),bs.begin()+i+1,v[i]) - bs.begin();
            bs[x] = v[i];
            idx[x].push_back(i);
        }
        int LIS = lower_bound(all(bs),INT_MAX)-bs.begin();
        vi res(LIS);
        res[LIS-1] = idx[LIS-1].back();
        for(int i = LIS-2 ; i >= 0 ; i--){
            auto it = *prev(lower_bound(all(idx[i]),res[i+1]));
            res[i] = it;
        }
        return res;
}


int lengthOfLIS(vector<int>& v) {   // O(n^2)

        v.insert(v.begin(),INT_MIN);
        
        int dp[2501];
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
