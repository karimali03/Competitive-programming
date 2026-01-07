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

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vector<vector<array<int,2>>>g(n);
    for(int i = 0;i < m; i++){
        int x,y; char c; cin>>x>>y>>c; x--,y--;
        g[x].push_back({y,c == 'B'});
        g[y].push_back({x,c == 'B'});
    }   
    vi ans(n+1);
    bool valid = false;
    for(auto color : {0,1}){
        vi col(n,-1);
        vi cur;
        bool vld = true;
        set<int>s1,s2;
        function<void(int,int)> dfs = [&](int x,int c){
            col[x] = c;
            if(c) s1.insert(x);
            else s2.insert(x);
            for(auto [a,b] : g[x]){
                int nc = color == b ? c : 1 - c;
                if(col[a] == -1) dfs(a,nc);
                else if(col[a] != nc) vld = false;
            }
        };
        for(int i = 0 ; i < n ; i++) if(col[i] == -1){
            dfs(i,0);
            if(s1.size() > s2.size()) swap(s1,s2);
            for(auto it : s1) cur.push_back(it);
            s1.clear(),s2.clear();
        }
        if(!vld) continue;
        valid = true;
        if(cur.size() < ans.size())  ans = cur;
    }
    if(!valid) NA;
    else {
        cout<<ans.size()<<ln;
        for(auto &it : ans) cout<<it+1<<" ";
        cout<<ln;
    }
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