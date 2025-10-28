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
const int N = 35005;
const int K = 55;
int n,k;
int v[N];
int dp[K][N];
int frq[N]{};
int dis = 0;
int cur_l,cur_r;
void add(int i){
    frq[v[i]]++;
    if(frq[v[i]] == 1) dis++;
}
void rm(int i){
    frq[v[i]]--;
    if(frq[v[i]] == 0) dis--;
}



void calc(int cur,int l,int r,int optl,int optr){
    if(l>r) return;
    int mid = l + (r-l)/2;
    int kr = min(mid,optr);
    // expand
    while(cur_l > kr) add(--cur_l);
    while(cur_r < mid) add(++cur_r);
    // shrink
    while(cur_l < kr) rm(cur_l++);
    while(cur_r > mid) rm(cur_r--);
    
    pair<int,int> ans = {-1,-1};
    for(int x = kr ; x >= optl ; x--){
        ans = max(ans , {(x ? dp[cur-1][x-1] : 0) + dis ,x});
        if(x-1) add(--cur_l);
    }
    dp[cur][mid] = ans.first;
    int opt = ans.second;
    calc(cur,l,mid-1,optl,opt);
    calc(cur,mid+1,r,opt,optr);
}

void solve(int test_case) {
    cin>>n>>k;
    f(i,0,n) cin>>v[i];
    for(int i = 0;i < n ; i++){
        add(i);
        dp[1][i] = dis;
    }
    for(int cur = 2 ; cur <= k ; cur++){
        cur_l = cur_r = -1; 
        dis = 0;
        f(i,0,n+1) frq[i] = 0;
        calc(cur,0,n-1,0,n-1);
    }
    cout<<dp[k][n-1]<<ln;
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