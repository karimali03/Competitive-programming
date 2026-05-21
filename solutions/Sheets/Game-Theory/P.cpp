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

map<int,int>dp;
vector<int>opt = {2,3,4,5,6};
int get(int x){
    if(x == 0) return 0;
    if(dp.count(x)) return dp[x];
    bool vis[6]{};
    for(auto &it : opt){
        if(it&1) vis[get(x/it)] = 1;
        else vis[0] = 1;
    }
    int mex = 0;
    while(vis[mex]) mex++;
    return dp[x] = mex;
}

void solve(int test_case) {
    int n; cin>>n;
    int xr = 0;
    int prv = 0 , c = 0;
    vi rng;
    int l = 1 , val = 2;
    while(true){
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; val *= 3;
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val;
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; val *= 5;
    }
    rng.push_back(INT64_MAX);
    cout<<rng<<ln;
    // auto get2 = [&](int x) -> int{
    //     auto it = (upper_bound(all(rng),x) - rng.begin())%3;
    //     if(it == 0) return 3;
    //     return it;
    // };
    for(int i = 0 ;i <= 100000 ; i++){
        int x = get(i);
        // int y = get2(i);
        // if(x != y) cout<<i<<" "<<x<<" "<<y<<ln;
    } 
    // if(xr)
    // cout<<"Derek\n";
    // else 
    // cout<<"Henry\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}