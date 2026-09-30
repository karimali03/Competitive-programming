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
    int n,m,k; cin>>n>>m>>k;
    vector<pair<int,int>>as(n);
    for(int i=0;i<n;i++){
        cin>>as[i].first>>as[i].second;
    }
    map<int,vi>mp;
    set<pair<int,int>>st;
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y;
        st.insert({x,y});
        mp[x].push_back(y);
    }
    for(auto &[x,y]:  as) if(mp.count(x)) mp[x].push_back(y);
    for(auto &[a,b] : mp){
        sort(all(b));
        for(auto &it : b){
            if(st.count({a,it})) it = 1;
            else it = 0;
        }
    }
    vi dp(k+1,1e9);
    dp[0] = 0;
    for(auto &[x,v] : mp){
        for(int i = k-1 ; i >= 0 ; i--){
           int sm = 0; int c = 0;
           for(auto &it : v){
                sm += it; c++;
                dp[min(k,i+sm)] = min( dp[min(k,i+sm)] ,c + dp[i]);
           } 
        }
    }
    cout<<dp[k]<<ln;

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