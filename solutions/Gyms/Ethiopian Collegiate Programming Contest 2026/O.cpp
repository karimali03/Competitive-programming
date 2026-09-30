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
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vii g(n);
    for(int i = 1;i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi node; queue<int>q; q.push(0); 
    vi par(n,-1); 
    while(!q.empty()){
        auto c = q.front();q.pop();
        node.push_back(c);
        for(auto &it : g[c]){
            if(par[c] == it) continue;
            par[it] = c; q.push(it);
        }
    }
    auto can = [&](int x) -> bool{
        vi sum(n);
        int tk = 0;
        for(int i = n-1 ; i >= 0 ; i--){
            int u = node[i];
            vi ch;
            for(auto &it : g[u]) if(it != par[u]) ch.push_back(sum[it]);
            sort(all(ch));
            sum[u] = v[u];
            for(auto &it : ch){
                if(sum[u] + it <= x) sum[u] += it;
                else tk++;
            }
        }
        return tk <= k;
    };
    int l = *max_element(all(v));
    int r = 0;
    for(int i=0;i<n;i++) r+=v[i];
    int ans = r;
    while(l<=r){
        int m = l + (r-l)/2;
        if(can(m)){
            ans = m;
            r = m-1;
        }else{
            l = m+1;
        }
    }
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}