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

const int MOD = 1e9+7;
int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b>>=1;
    }

    return res;
}
void solve(int test_case) {
    int n; cin>>n;
    vii g(n);
    vi dg(n);
    for(int i = 1 ; i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        for(auto it : g[u]){
            if(it == p) continue;
            dg[u]++;
            dfs(it,u);
        }
    };
    dfs(0,-1);
    vi vis(n);
    queue<int>q;
    f(i,0,n) if(dg[i] == 0) q.push(i);
    int ac = n;
    int res = fp(2,n-1) * ac;
    while(!q.empty()){
        int sz = q.size();
        ac-=sz;
        while(sz--){
            auto it = q.front(); q.pop();  vis[it] = 1;
            for(auto x : g[it]){
                dg[x]--;
                if(dg[x] == 0) q.push(x);
            }
        }
     //   cout<<ac<<" ";
        (res+=fp(2,n-1)*ac)%=MOD;
    }
    cout<<res<<ln;
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