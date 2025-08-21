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

/*
============================ BLOCK-CUT TREE TEMPLATE ============================

USAGE:
- Use for undirected graphs to find:
    - Biconnected components (BCCs)
    - Articulation points (cutpoints)
    - Block-Cut Tree (BCT) for path queries, LCA, etc.

INPUT:
- Graph `g` as adjacency list
- 0-based node indices

OUTPUT:
- is_cutpoint[u] → true if `u` is a cutpoint
- id[u] → maps original node `u` to a node in the block-cut tree
- blockcut_tree → tree of cutpoints and BCCs (size ≤ 2 * n)

NOTES:
- Each node in blockcut_tree is either:
    - A cutpoint (if u is articulation point, id[u] points to a unique node)
    - A BCC node (if u is non-articulation, id[u] points to its BCC node)
- Use `id[a]`, `id[b]`, etc. for LCA or path queries in blockcut_tree

=================================================================================
*/
vector<vector<int>> biconnected_components(vector<vector<int>> &g,
                                           vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();

	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n), low(n);
	is_cutpoint.assign(n, false);

	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : g[node]) {
			if (son == parent) continue;
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};

	int timer = 0;
	dfs(0, -1, timer);
	id.resize(n);

	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);  // dummy
		int node_id = 1;

		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}

		for (auto &comp : comps) {
			int new_node = node_id++;
			t.push_back({});
			for (int u : comp) {
				if (!is_cutpoint[u]) {
					id[u] = new_node;
				} else {
					t[new_node].push_back(id[u]);
					t[id[u]].push_back(new_node);
				}
			}
		}
		t.erase(t.begin());  // remove dummy
		for (int i = 0; i < (int)t.size(); ++i) {
			for (int &x : t[i]) if (x > 0) x--;
		}
		for (int &x : id) if (x > 0) x--;
		return t;
	};

	return build_tree();
}


vector<int>vld;
const int LOG = 20;
struct LCA{
    int n;
    vii adj,up,val;
    vi lvl;
    LCA(int n,vii adj,int root = 0):n(n),adj(adj){
        lvl = vi(n);
        val = up = vii(n,vi(LOG));
        for (int i = 0; i < n; ++i) {
            adj[i].clear();
            lvl[i] = 0;
            for (int j = 0; j < LOG; ++j) {
                up[i][j] = 0;
                val[i][j] = 0;
            }
        }
        lvl[root] = 0;
        up[root][0] = root;
        val[root][0] = 0;
        for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
            val[root][j] = 0;
        }
        dfs(root,-1);
    }
    int merge(int a,int b){
        return a+b;
    }
    
    void dfs(int v,int p){
        for(auto to : adj[v]){
            if(to == p) continue;
            lvl[to] = lvl[v] + 1;
            up[to][0] = v;
            val[to][0] = vld[to];
            for(int j = 1 ; j < LOG; j++){
                up[to][j] = up[up[to][j-1]][j-1];
                val[to][j] = merge(val[to][j-1],val[up[to][j-1]][j-1]);
            }
            dfs(to,v);
        }
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
        
    
            
    int get(int u,int v){
            int lc = lca(u,v);
            int dif1 = lvl[u] - lvl[lc];
            int dif2 = lvl[v] - lvl[lc];
            int res = 0;
            for(int j = LOG-1 ; j >= 0 ; j--){
                if ((dif1 >> j) & 1) {
                    res += val[u][j];
                    u = up[u][j];
                }
                if ((dif2 >> j) & 1) {
                    res += val[v][j];
                    v = up[v][j];
                }
            }
        
            return res + vld[lc];
    }
};


void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii g(n);
    for(int i=0;i<m;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi id;
    vector<bool>arc;
    auto bct = biconnected_components(g,arc,id);
    int sz = bct.size();
    vld = vi(sz);
    for(int i=0;i<n;i++) if(arc[i]) vld[id[i]] = 1;
   
    LCA lc(sz,bct);
    int q; cin>>q;
    while(q--){
        int x,y; cin>>x>>y; x--,y--;
      
        int res = lc.get(id[x],id[y]) - vld[id[x]] - vld[id[y]];
        cout<<res<<ln;
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