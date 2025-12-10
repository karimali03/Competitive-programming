const int N = 200005;
int dp[N][3];
int vis[N][3]{};
// 0 0 0 0 0 1 1 1 1 1 2 2 2 2 2 
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    function<int(int,int)> rec=[&](int i,int st) ->int{
        if(i == n) return st == 2 ? 0 : INT64_MIN;
        int &ret = dp[i][st];
        if(vis[i][st]) return ret;
        if(st == 0) ret = max(rec(i+1,st),rec(i+1,st+1));
        else if(st == 1) ret = v[i] + max(rec(i+1,st),rec(i+1,st+1));
        else ret = rec(i+1,st);
        vis[i][st] = 1;
        return ret;
    };
    cout<<max(rec(0,0),rec(0,1))<<ln; 
}

