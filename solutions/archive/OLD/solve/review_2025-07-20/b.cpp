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


const int OO = 1e17;
struct edge {
        int from, to, w;
        edge(int from=0, int to=0, int w=0) :
        from(from), to(to), w(w) {
        }
};

void dfs(int u,vi &node , vii &g){
    node[u] = 1;
    for(auto it : g[u]){
        if(!node[it]) dfs(it,node,g);
    }
}
pair<bool,vector<int>> BellmanFord(vector<edge> &edgeList,vii&g,int n, int src) {
        vector<int> dist(n, OO);
        bool neg_cycle = false;
        dist[src] = 0;
        vi node(n);
        for (int it = 0; it < n ; ++it) {
            bool any_updates = false;
            for (int j = 0; j < (int) edgeList.size(); ++j) {
                edge &ne = edgeList[j];	
                if (dist[ne.to] > dist[ne.from] + ne.w) {
                    dist[ne.to] = dist[ne.from] + ne.w;
                    if(it == n-1){
                        node[ne.from] = 1;
                        node[ne.to] = 1;
                    }
                    any_updates = true;
                }
            }
            if(!any_updates) break;
            if(it == n-1) neg_cycle = true;   
        }
        if(!neg_cycle) return {false , dist};
        vi vis(n);
        dfs(0,vis,g);
        for(int i=0;i<n;i++) if( vis[i] &&  node[i]) dfs(i,node,g);
        if(node[n-1]) return {true , dist};
        return {false , dist};
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vector<edge>v(m);
    vector<vector<int>>g(n);
    for(int i = 0; i < m ;i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        v[i] = {x,y,-z};
        g[x].push_back(y);
    }
    auto [_ , dist] = BellmanFord(v,g,n,0);
    if(_) cout<<-1<<ln;
    else cout<<-dist[n-1]<<ln;
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