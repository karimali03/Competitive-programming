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
    int n; cin>>n;
    vi v(n); cin>>v;
    vii g(n+1);
    priority_queue<int,vi,greater<>>q;
    q.push(v[0]);
    vector<pair<int,int>> edg;
    for(int i = 1 ; i < n ; i++){
        int new_mn = v[i];
        while(!q.empty() && q.top() < v[i]){
            g[q.top()].push_back(v[i]);
            edg.push_back({q.top(),v[i]});
            g[v[i]].push_back(q.top());
            new_mn = min<ll>(q.top() , new_mn);
            q.pop();
        }
        q.push(new_mn);
    }

    vi vis(n+1);
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto it : g[x]) if(!vis[it]) dfs(it);
    };
    int cnt = 0;
    f(i,0,n) if(!vis[v[i]]) cnt++,dfs(v[i]);
    if(cnt == 1){
        YES;
        assert((int)edg.size() == n-1);
        for(auto [a,b] : edg) cout<<a<<" "<<b<<ln;
    }
    else NO;
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