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
    int n,t; cin>>n>>t;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vii dp(n,vi(2,-1));
    function<int(int,int,int)> rec = [&](int x,int p,int ch){
        int &ret = dp[x][ch];
        if(~ret) return ret;
        bool vld = false;
        for(auto it : g[x]) if(it != p){
            if(!rec(it,x,1-ch)) vld = true;
        }
        if(vld) return ret = 1;
        return ret = 0;
    };
    rec(0,-1,0);
    rec(0,-1,1);
    vi ans(n);
    function<void(int,int)> reroot = [&](int x,int p){
        ans[x] = dp[x][0];
        int N = g[x].size();
        vi pre(N+1),suf(N+2);
        for(int i = 0 ; i < N ; i++) pre[i+1] = pre[i] | (dp[g[x][i]][1] == 0);
        for(int i = N-1 ; i >= 0 ; i--) suf[i+1] = suf[i+2] | (dp[g[x][i]][1] == 0);
        vi pre2(N+1),suf2(N+2);
        for(int i = 0 ; i < N ; i++) pre2[i+1] = pre2[i] | (dp[g[x][i]][0] == 0);
        for(int i = N-1 ; i >= 0 ; i--) suf2[i+1] = suf2[i+2] | (dp[g[x][i]][0] == 0);
        for(int i = 0 ; i < N ; i++){
            int it = g[x][i]; 
            if(it == p) continue;
            pair<int,int> org = {dp[x][0] , dp[x][1]};
            dp[x][0] = pre[i] | suf[i+2];
            dp[x][1] = pre2[i] | suf2[i+2];
            dp[it][0] = dp[it][0] | !dp[x][1];
            dp[it][1] = dp[it][1] | !dp[x][0];
            reroot(it,x);
            dp[x][0] = org.first;
            dp[x][1] = org.second;
        }
    };

    reroot(0,-1);
    for(int i = 0 ; i < t ; i++){
        int x; cin>>x; x--;
        if(!ans[x]) cout<<"Hermione\n";
        else cout<<"Ron\n";
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