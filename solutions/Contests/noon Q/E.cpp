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

const int N = 10005;
bitset<N> dp[N];
void solve(int test_case) {
    int n; cin>>n;
    vii g(n);
    f(i,0,n){
        dp[i] = 0;
        dp[i][i] = 1;
    }
    for(int i = 0;i < n ; i++){
        int x; cin>>x;
        f(j,0,x){
            int c; cin>>c; c--;
            g[i].push_back(c);
        }
    }
    vi vis(n);
    vi ret;
    
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto it : g[x]){
            if(!vis[it]) dfs(it);
        }
        vis[x] = 2;
        ret.push_back(x);
    };
    f(i,0,n) if(!vis[i]) dfs(i);
    reverse(all(ret));
    bitset<N> cur;
    for(auto it : ret){
        for(auto x : g[it]){
            cur = (dp[x]&dp[it]);
            if(cur != 0){
                YES; return;
            }
            dp[x] |= dp[it];
        }
    }
    NO;
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