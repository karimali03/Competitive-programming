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
#define ld long double

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


bool dist(array<int,3> &a,array<int,3> & b){
    ld dist = sqrtl((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1])) - a[2]/2.0 - b[2]/2.0;
    return dist <= 50.8;
} 

void solve(int test_case) {
    int n; cin>>n;
    vector<array<int,3>> v(n);
    map<pair<int,int>,vi> id;
    for(int i = 0;i < n ; i++){
        int x,y,d; cin>>x>>y>>d;
        v[i] = {x,y,d};
        id[{x/220,y/220}].push_back(i);
    }
    vii adj(n);
    for(int i = 0;i < n ; i++){
        int x = v[i][0]/220 , y = v[i][1]/220;
        for(int dx = -1 ; dx <= 1 ; dx++){
            int di = dx + x;
            for(int dy = -1 ; dy <= 1 ; dy++){
                int dj = dy + y;
                if(id.count({di,dj})){
                    for(auto &idx : id[{di,dj}]){
                        if(idx == i) continue;
                        if(dist(v[i],v[idx])) adj[i].push_back(idx);
                    }
                }
            }
        }
    }

    bool vld = true;
    vi vis(n);
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto &it : adj[x]) if(!vis[it]) dfs(it);
    };
    dfs(0);
    for(int i = 1 ; i < n ; i++) if(!vis[i]) vld = false;
    if(n >= 7){
        for(int i = 0;i < n ; i++){
            if((int)adj[i].size() < 2) vld = false;
          //  cout<<i<<" : ";
          //  for(auto it : adj[i]) cout<<it<<" ";
          //  cout<<ln;
        }
    }

    if(vld) cout<<"yes\n";
    else cout<<"no\n";
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