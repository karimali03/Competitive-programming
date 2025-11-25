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
const int K = 105;
int n,k;
int v[N];
int dp[K][N];
deque<int> st[N];
int res = 0;
int cur_l,cur_r;
void add(int i){
    if(!st[v[i]].empty()) res -= (st[v[i]].back() - st[v[i]].front());
    if(st[v[i]].empty() || st[v[i]].back() < i) st[v[i]].push_back(i);
    else st[v[i]].push_front(i);
    res +=  st[v[i]].back() - st[v[i]].front();
}
void rm(int i){
    if(!st[v[i]].empty()) res -= (st[v[i]].back() - st[v[i]].front());
    if(st[v[i]].front() == i) st[v[i]].pop_front();
    else st[v[i]].pop_back();
    if(!st[v[i]].empty())  res +=  st[v[i]].back() - st[v[i]].front();
}

void move(int l,int r){
    // expand 
    while(cur_l > l) add(--cur_l);
    while(cur_r < r) add(++cur_r);
    // shrink
    while(cur_l < l) rm(cur_l++);
    while(cur_r > r) rm(cur_r--);
}

void calc(int cur,int l,int r,int optl,int optr){
    if(l>r) return;
    int mid = l + (r-l)/2;
    int kr = min(mid,optr);
    int ans = 1e9;
    int opt = optl;
    for(int x = kr ; x >= max(cur,optl) ; x--){
        move(x,mid);
        int cur_ans = dp[cur-1][x-1] + res;
        if(cur_ans < ans){
            ans = cur_ans;
            opt = x;
        }
    }
    dp[cur][mid] = ans;
    calc(cur,l,mid-1,optl,opt);
    calc(cur,mid+1,r,opt,optr);
}
void solve(int test_case) {
    cin>>n>>k;
    f(i,0,n) cin>>v[i];
    
    for(int i = 0;i < n ; i++){
        add(i);
        dp[0][i] = res;
    }
    for(int x = 1 ; x < k ; x++){
        cur_l = 0; cur_r = -1;
        res = 0;
        f(i,0,n+1) st[i].clear();
        calc(x,0,n-1,0,n-1);
    }
    cout<<dp[k-1][n-1]<<ln;
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