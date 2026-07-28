#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii g(n);
    /*
        some has Frined ships 
        Rule no two non frieds in same team

    */
    for(int i = 0; i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }   
    if(n%2){
        cout<<"impossible\n";
        return;
    }
    int md = n/2;
    for(int i = 0;i < n ; i++){
        sort(all(g[i]));
        g[i].erase(unique(all(g[i])),g[i].end());
        if((int)g[i].size() < md-1){
            cout<<"impossible\n";
            return;
        }
    }
    vii rg(n,vi(n,1));
    for(int i = 0;i < n ; i++){
        rg[i][i] = 0;
        for(auto &it : g[i]){
            rg[i][it] = 0;
        }
    }
    
    vi vis(n);
    bool vld = true;
    array<int,2> C = {0,0};
    function<void(int,int)> dfs = [&](int x,int c) -> void {
        if(vis[x]){
            if(vis[x] != c) vld = false;
            return;
        }
        C[c-1]++;
        vis[x] = c;
        for(int i = 0;i < n ; i++){
            if(rg[x][i]) dfs(i,3-c);
        }
    };
    vector<array<int,3>> cmp;
    // for(int i = 0;i <  n;  i++){
    //     for(int j = 0;j < n ; j++) cout<<rg[i][j]<<" ";
    //     cout<<ln;
    // }
    for(int i = 0;i < n ; i++){
        if(!vis[i]){
            C = {0,0};
            dfs(i,1);
          //  cout<<C[0]<<" "<<C[1]<<" "<<i<<"\n";
            cmp.push_back({C[0],C[1],i});
        }
    }
    if(!vld){
        cout<<"impossible\n";
        return;
    }
    // cout<<"..."<<endl;
    int sz = cmp.size();
    vector<vector<bool>> dp(sz+1,vector<bool>(md+1));
    dp[0][0] = true;
    // push state to future
    for(int i = 0 ; i < sz ; i++){
         auto [a,b,c] = cmp[i];
        for(int sum = 0; sum <= md ; sum++){
            if(!dp[i][sum]) continue;
            if(sum + a <= md){
                dp[i+1][sum+a] = true;
            }
            if(sum + b <= md){
                dp[i+1][sum+b] = true;
            }
        }
    }
    if(!dp[sz][md]){
        cout<<"impossible\n";
        return;
    }
    int cur = md;
    vi vis2(n);
    vi res(n);
    function<void(int,int,int)> chk = [&](int x,int c,int tag){
        if(vis2[x]) return;
        vis2[x] = c;
        if(tag == c) res[x] = c;
        for(int i = 0;i < n ; i++){
            if(rg[x][i]) chk(i,3-c,tag);
        }
    };
    for(int i = sz ; i > 0 ; i--){
        auto [a,b,c] = cmp[i-1];
        if(cur-a >=0  && dp[i-1][cur-a]){
            cur -= a;
            chk(c,1,1);
        }else{
            cur -= b;
            chk(c,1,2);
        }
    }
    for(int i  =0;i <  n; i++){
         if(res[i]) cout<<"r\n";
         else cout<<"b\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}