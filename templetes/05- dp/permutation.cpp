const int N = 3005;
int dp[N][N];
int sdp[N][N];
const int MOD = 1e9+7;
void solve(int test_case) {
    int n; cin>>n;
    string s; cin>>s;
    memset(dp,-1,sizeof(dp));
    memset(sdp,-1,sizeof(sdp));
    function<int(int,int)> prefix; 
    function<int(int,int)> rec = [&](int i,int prv) -> int{
        if(i == n) return 1;
        int &ret = dp[i][prv];
        if(~ret) return ret;
        ret = 0;
        // 1 -> i+1
        if(s[i-1] == '<'){
            // prv+1 -> i+1
            ret = (prefix(i+1,i+1) - prefix(i+1,prv) + MOD)%MOD;
        }else{
            // 1 -> prv
            ret = prefix(i+1,prv);
        }
        return ret;
    };
    prefix = [&](int i,int idx) -> int{
        if(idx == 0) return 0;
        int &ret = sdp[i][idx];
        if(~ret) return ret;
        return ret = (rec(i,idx)%MOD + prefix(i,idx-1)%MOD)%MOD;
    };
    cout<<rec(1,1)<<ln;
}


//-----------------------------------------------------------------------------------------------------------------
const int N = 3005;
int dp[N][N]{};
const int MOD = 1e9+7;
void solve(int test_case) {
    int n; cin>>n;
    string s; cin>>s;
    dp[0][1] = 1;
    for(int i = 1 ; i < n ; i++){
        for(int x = 1 ; x < n ; x++) (dp[i-1][x] += dp[i-1][x-1])%=MOD;
        for(int prv = 1 ; prv <= i+1 ; prv++){
            if(s[i-1] == '<'){
                dp[i][prv] = (dp[i-1][prv-1] - dp[i-1][0] + MOD)%MOD;
            }else{
                dp[i][prv] = (dp[i-1][i] - dp[i-1][prv-1] + MOD)%MOD;
            }
        }
    }
    int res = 0;
    for(int i = 1 ; i <= n ; i++) (res+=dp[n-1][i])%=MOD;
    cout<<res<<ln;
}


