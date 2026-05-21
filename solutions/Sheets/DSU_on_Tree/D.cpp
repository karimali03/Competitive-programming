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


const int N = 500005;
int sz[N] , big[N] , dep[N];
vector<int>g[N];
int color[N];
// Global data structure (e.g., frequency array, max variables)
int freq[N][26]{}; 
int od[N]{};
// answer
vector<pair<int,int>>qu[N];
ll ans[N];
// preprocess the tree to compute sizes and identify big children 
void pre(int x,int d){
    sz[x] = 1;
    dep[x] = d;
    big[x] = -1;
    for(auto &y : g[x]){
        pre(y,d+1);
        sz[x] += sz[y];
        if( big[x] == -1 || sz[y] > sz[big[x]]) big[x] = y;
    }
}

void upd(int x,int d){
    int ch = color[x];
    int h = dep[x];
    if(freq[h][ch]&1) od[h]--;
    freq[h][ch] += d;
    if(freq[h][ch]&1) od[h]++;
}

// add or remove the contribution of a subtree rooted at 'x' to the global data structure
void add(int x,int p,int d){
    upd(x,d);
    for(auto &it : g[x]) if(it != p){
        add(it,x,d);
    }
}

int n,m; 
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
    for(auto &[h,idx] : qu[x]){
        if(od[h] <= 1) ans[idx] = 1;
    }
    // remove if required
    if(!keep) add(x,p,-1);
}



void solve(int test_case) {
   cin>>n>>m;
   for(int i = 1; i < n ; i++){
        int x; cin>>x; x--;
        g[x].push_back(i);
   }
   for(int i =0 ;i < n ;i++){
        char ch; cin>>ch;
        color[i] = ch-'a';
   }
   for(int i = 0 ; i < m ; i++){
        int x,y; cin>>x>>y; x--;
        qu[x].push_back({y,i});
   }
   pre(0,1);
   sack(0,-1,1);
   f(i,0,m){
        if(ans[i]) cout<<"Yes\n";
        else cout<<"No\n";
   }
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