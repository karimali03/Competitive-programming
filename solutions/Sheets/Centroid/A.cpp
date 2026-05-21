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


const int N = 200005;
vector<int> g[N];
int sz[N];
bool del[N];
// data structures
int cnt[2][N]{};
int C[30][2]{};
int val[N];
ll ans = 0;
int get_size(int u,int p){
    sz[u] = 1;
    for(auto &it : g[u]) if(it != p && !del[it]){
        sz[u] += get_size(it,u);
    }
    return sz[u];
}
int get_centroid(int u,int p,int tot){
    for(auto &it : g[u]) if(it != p && !del[it]){
        if(sz[it] * 2 > tot) return get_centroid(it,u,tot);
    }
    return u;
}

void compute(int cur,int delta){
    for(int i = 0;i < 20 ; i++){
        if((cur>>i)&1) C[i][1] += delta;
        else C[i][0] += delta;
    }
}
void add(int u,int p,int cur,int delta){
    // add me 
    cur = cur ^ val[u];
    compute(cur,delta);
    for(auto &it : g[u]) if(it != p && !del[it]){
        add(it,u,cur,delta);
    }
}
void calc(int u,int p,int cur){
    // calc answer for u
    cur = cur ^ val[u];
    for(int i = 0;i < 20 ; i++){
        if((cur>>i)&1) ans += (ll)(1 << i) * (ll)C[i][0];
        else ans += (ll)(1 << i) * (ll)C[i][1];
    }
    for(auto &it : g[u]) if(it != p && !del[it]){
        calc(it,u,cur);
    }
}
void decompose(int x){
    int cent = get_centroid(x,-1,get_size(x,-1));
    // calc answer for this centroid
    compute(val[cent],1);
    for(auto &it : g[cent]) if(!del[it]){
        calc(it,cent,0);
        add(it,cent,val[cent],1);
    }
    // clear datastructure for next centroid
    compute(val[cent],-1);
    for(auto &it : g[cent]) if(!del[it]){
        add(it,cent,val[cent],-1);
    }
    del[cent] = true;
    // decompose for next centroid
    for(auto &it : g[cent]) if(!del[it]){
        decompose(it);
    }
}

void solve(int test_case) {
    int n; cin>>n;
    ans = 0;
    f(i,0,n){
        cin>>val[i];
        ans += val[i];
    }
    for(int i = 1 ; i < n; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    decompose(0);
    cout<<ans<<ln;
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