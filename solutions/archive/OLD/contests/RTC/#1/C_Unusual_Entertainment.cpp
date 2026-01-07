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

int n; 
vii adj;
vi mp;
vi v;

vector<int> time_in, time_out;
int dfs_timer;

void dfs(int i , int p) {
    time_in[i] = ++dfs_timer;
    v.push_back(mp[i]);
    for (int u : adj[i]){
        if(u == p) continue;
        dfs(u,i);
    }
    time_out[i] = dfs_timer;
}



struct SegmentTree {
    struct node {
        vi v;
    };

    int n;
    vector<node> tree;
    node neutral = { {INT_MIN} };  // Change for different operations

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        vi merged;
        int i = 0 , j = 0 , k = 0;
        while(i < a.v.size() && j < b.v.size()){
            if(a.v[i] < b.v[j])  merged.push_back(a.v[i++]);
            else merged.push_back(b.v[j++]);
        }
        while(i < a.v.size()) merged.push_back(a.v[i++]);
        while(j < b.v.size()) merged.push_back(b.v[j++]);

        return { merged };
    }

    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = { {a[tl]} };
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query in range [l, r]
    bool query(int v, int tl, int tr, int l, int r , int lv , int rv) {
        if (l > r) return 0;
        if (l == tl && r == tr){
            int lx  = 0  , rx = tree[v].v.size()-1;
            while(lx <= rx){
                int mid = lx + (rx-lx)/2;
                if(tree[v].v[mid] >= lv && tree[v].v[mid] <= rv) return true;
                if(tree[v].v[mid] < lv){
                    lx = mid+1;
                }
                else rx = mid-1;
            }   
            return false;
        }
        int tm = (tl + tr) / 2;
        auto left = query(v * 2 + 1, tl, tm, l, min(r, tm) , lv,rv);
        auto right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r , lv,rv);
        return left || right;
    }

};

void solve(int test_case) {
    int q; cin>>n>>q;
    adj = vii(n);
    mp = time_in = time_out  = vi(n);
    dfs_timer = -1;
    v.clear();

    for(int i  =0 ,u,v ; i <n-1;i++){
        cin>>u>>v; u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
   
    f(i,0,n){
        int x; cin>>x; x--;
        mp[x] = i;
    } 

    dfs(0,-1);
    SegmentTree st(n);
    st.build(v,0,0,n-1);
    // for(int i  =0 ; i < n ; i++){
    //     cout<<time_in[i]<<" "<<time_out[i]<<ln;
    // }
    // debug(v);


    while(q--){
        int l,r,x; cin>>l>>r>>x; l--,r--,x--;
        if(st.query(0,0,n-1,time_in[x],time_out[x],l,r)) cout<<"YES\n";
        else cout<<"NO\n";
    }
    cout<<ln;
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