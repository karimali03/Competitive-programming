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


const int N = 200005;
vector<int> g[N];
int sz[N]{};
vector<int> centroids;
int n;
// A centroid is a node such that if you remove it, 
// no remaining connected component has a size greater than N/2
void get_centroids(int u, int p) {
    sz[u] = 1;
    bool is_centroid = true;

    for (int v : g[u]) {
        if (v == p) continue;
        
        get_centroids(v, u);
        sz[u] += sz[v];
        
        // Check if child's component is too big
        if (sz[v] > n / 2) is_centroid = false;
    }

    // Check if parent's component is too big
    if (n - sz[u] > n / 2) is_centroid = false;

    if (is_centroid) {
        centroids.push_back(u);
    }
}

void solve(int test_case) {
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    get_centroids(0,-1);
    
    vi cnt(n);
    bool vld = true;
    function<void(int,int)> dfs = [&](int x,int p){
        cnt[x] = 1;
        vi ch;
        for(auto &it : g[x]) if(it != p){
            dfs(it,x);
            ch.push_back(cnt[it]);
        }
        sort(all(ch));
        for(auto &it : ch){
            if(it > cnt[x]) vld = false;
            cnt[x] += it;
        }
    };
    bool res = false;
    for(auto it : centroids){
        cnt.clear(); 
        vld = true;
        dfs(it,-1);
        res |= vld;
    }
    if(res) YES;
    else NO;

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