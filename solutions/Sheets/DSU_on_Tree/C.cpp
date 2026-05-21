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

/*
   sack on tree N log N * u, where u is the time taken to update the global data structure.
   used to answer queries on subtrees of a tree.
*/
const int N = 200005;
int sz[N] , big[N];
vector<int>g[N];
int color[N];
// Global data structure (e.g., frequency array, max variables)
int freq[N]{}; 
ll sum[N]{};
int mx = 0;
// answer
ll ans[N];
// preprocess the tree to compute sizes and identify big children 
void pre(int x,int p){
    sz[x] = 1;
    big[x] = -1;
    for(auto &y : g[x]) if(y != p){
        pre(y,x);
        sz[x] += sz[y];
        if( big[x] == -1 || sz[y] > sz[big[x]]) big[x] = y;
    }
}

void upd(int x,int d){
    int cl = color[x];
    if(freq[cl] + d > mx) mx++;
    else if(freq[cl] == mx && sum[mx] == cl) mx--;

    sum[freq[cl]] -= cl;
    freq[cl] += d;
    sum[freq[cl]] += cl;
}

// add or remove the contribution of a subtree rooted at 'x' to the global data structure
void add(int x,int p,int d){
    upd(x,d);
    for(auto &it : g[x]) if(it != p){
        add(it,x,d);
    }
}

void sack(int x,int p,int keep){
    // add and remove light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) sack(it,x,0);
    // add big child
    if(~big[x]) sack(big[x],x,1);
    // add myself
    upd(x,1);
    // add light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) add(it,x,1);
    // answer queries
    ans[x] = sum[mx];
    // remove if required
    if(!keep){
        add(x,p,-1);
        /* * HARD RESET:
         * Because add(..., -1) destroyed the entire subtree, the cnt array 
         * is exactly how we found it (empty). We can safely reset our global 
         * trackers to 0 without recalculating anything.
         * ex : mx = 0 , mn = 0
         */
    } 
}



void solve(int test_case) {
   int n; cin>>n;
   f(i,0,n) cin>>color[i];
   f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
   }
   pre(0,-1);
   sack(0,-1,1);
   f(i,0,n) cout<<ans[i]<<" ";
   cout<<ln;
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