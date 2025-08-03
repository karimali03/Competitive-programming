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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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
vector<int>adj[N];
const int LOG = 17;
int up[N][LOG];
int lvl[N];

void init(int n){
    for (int i = 0; i < n; ++i) {
        adj[i].clear();
        lvl[i] = 0;
        for (int j = 0; j < LOG; ++j) {
            up[i][j] = 0;
        }
    }
}


void dfs(int v,int p){
    for(auto to : adj[v]){
        if(to == p) continue;
        lvl[to] = lvl[v] + 1;
        up[to][0] = v;
        for(int j = 1 ; j < LOG; j++){
            up[to][j] = up[up[to][j-1]][j-1];
        }
        dfs(to,v);
    }
}   

void build(int root = 0){
    lvl[root] = 0;
    up[root][0] = root;
    for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
    }
    dfs(root,-1);
}

int lca(int u,int v){
    if (lvl[u] < lvl[v]) swap(u, v);
    int diff = lvl[u] - lvl[v];
    for (int j = LOG - 1; j >= 0; --j)
            if ((diff >> j) & 1)  u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    return up[u][0];   
}


struct BIT {
    int n;
    vector<int> tree;

    BIT(int size) {
        n = size;
        tree.assign(n + 1, 0); // still size n+1, internal use is 1-based
    }

    // Add delta to index i (0-indexed)
    void update(int i, int delta) {
        i++; // internally work with 1-based
        while (i <= n) {
            tree[i] += delta;
            i += i & -i;
        }
    }

    // Get prefix sum [0..i] (0-indexed)
    int query(int i) {
        i++; // internally work with 1-based
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }

    // Range sum [l..r] (both 0-indexed)
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Set value at index i (0-indexed)
    void set(int i, int new_val) {
        int curr = range_query(i, i);
        update(i, new_val - curr);
    }
};




void solve(int test_case) {
    int n,q; cin>>n>>q;
    string s; cin>>s;
    s = '(' + s + ')';
    vi v(2*n); cin>>v;
    stack<int>st;
    int cur = 0;
    int mx = 0;
    vector<pair<int,int>>edg;
    for(int i = 1 ;i  < 2*n+1 ; i++){
        if(s[i] == '('){
            st.push(cur);
            edg.push_back({cur,mx+1});
            cur = ++mx;
        }
        else {
            cur = st.top(); st.pop();
        } 
    }
    init(mx);
    BIT rng(mx);
    vi id(2*n,-1);
    int c = 1;
    f(i,1,2*n) if(s[i] == '(') id[i]=c++;
    
    for(auto [a,b] : edg){
        adj[a].push_back(b);
    }
    build(0);
    
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int l1,r1,l2,r2,val; cin>>l1>>r1>>l2>>r2>>val;
        }else{
            int l,r; cin>>l>>r;
        }
    }

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