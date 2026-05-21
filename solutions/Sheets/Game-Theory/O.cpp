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
        vis[get(x/it)] = 1;
    }
    int mex = 0;
    while(vis[mex]) mex++;
    return dp[x] = mex;
}

vi rng;
int get2(int x){
    if(x < 6){
        if(x == 1) return 1;
        if(x < 4) return 2;
        return 3;
    }
    auto it = (upper_bound(all(rng),x) - rng.begin() - 1)%4;
    return it;
}
void solve(int test_case) {
    int n; cin>>n;
    int xr = 0;
    for(int i = 0;i < n ; i++){
        int x; cin>>x;
        xr ^= get2(x);
    }  
    if(xr)
    cout<<"Henry\n";
    else 
    cout<<"Derek\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    
    int l = 6, val = 6;
    while(true){
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; val *= 2;
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; val*=2;
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; 
        rng.push_back(l);
        if(l > 1e18-val) break;
        l += val; val *= 3;
    }
    rng.push_back(INT64_MAX);
    // cout<<rng<<ln;
    // int prv = 0 , c = 0;
    // for(int i = 1 ; i <= 10000 ; i++){
    //     int x = get(i);
    //     int y = get2(i);
    //     if(x != y) cout<<i<<" "<<x<<" "<<y<<ln;
        // if(x == prv) c++;
        // else{
        //     cout<<prv<<" "<<c<<ln;
        //     prv = x , c = 1;
        // }
    // }
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
        
    return 0;
}