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
    int n,x,y; cin>>n>>x>>y;
    vi v(n); cin>>v;
    vii val;
    vi vis(n);
    function<void(int)> dfs = [&](int a){
        if(a >= n || a < 0 || vis[a]) return;
        vis[a] = 1;
        val.back().push_back(a);
        dfs(a+x); dfs(a-x);
        dfs(a+y); dfs(a-y);
    };
    for(int i = 0; i < n ; i++){
        if(!vis[i]){
            val.push_back({});
            dfs(i);
        }
    }
    vii va = val;
    for(auto &it : val){
        sort(all(it),[&](int a,int b){
            return v[a] < v[b];
        });
     //   cout<<it<<ln;
    }
    vi res(n);
    for(int i = 0; i < (int)val.size(); i++){
        sort(all(va[i]));
        for(int j = 0;j < (int)val[i].size() ; j++){
            int idx = va[i][j];
            int nw = val[i][j];
            res[idx] = v[nw]; 
        }
    }
 //   cout<<res<<ln;
    for(int i = 1;i < n ; i++){
        if(res[i] < res[i-1]){
            NO;
            return;
        }
    }
    YES;

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