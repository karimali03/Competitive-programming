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
    vii g(n);
    for(int i = 1;i < n ; i++){
        int x; cin>>x; x--;
        g[x].push_back(i);
    }
    vi val(n); 
    for(int i = 0;i < n; i++){
        cin>>val[i];
    }
    if(n == 1){
        YES;
        return;
    }
   
    bool vld = true;
    function<pair<int,int>(int)> dfs = [&](int x) -> pair<int,int> {
        if(g[x].empty()) return {val[x],val[x]};
        int sz = g[x].size();
        vector<pair<int,int>> ch(sz);
        int mn = -1;
        int mx = -1;
        int idx = -1;
        for(int i = 0;i < sz ; i++){
            auto cur = dfs(g[x][i]);
            if(idx == -1 || cur.first < mn){
                idx = i;
                mn = cur.first;
            }
            mx = max(mx , cur.second);
            ch[i] = cur;
        }
        if(!vld) return {0,0};
        int st = (idx+1)%sz;
        while(st != idx){
            int prv = (st-1+sz)%sz;
            if(ch[prv].second > ch[st].first){
                vld = false;
                return {0,0};
            }
            st = (st+1)%sz;
        }
        return {mn,mx};
    };
    dfs(0);
    if(vld){
        YES;
    }else NO;

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