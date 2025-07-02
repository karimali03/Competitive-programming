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



const int MAXV = 1005; // set according to problem constraints
const int INF = 1e9;

struct Dinic {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

    vector<Edge> adj[MAXV];
    int level[MAXV], ptr[MAXV];
    int s, t;

    void init(int _s, int _t) {
        s = _s;
        t = _t;
        for (int i = 0; i < MAXV; ++i)
            adj[i].clear();
    }

    void addEdge(int a, int b, int cap, bool directed = true) {
        adj[a].push_back({b, (int)adj[b].size(), cap, 0});
        adj[b].push_back({a, (int)adj[a].size() - 1, directed ? 0 : cap, 0});
    }

    bool bfs() {
        memset(level,-1,sizeof(level));
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : adj[v]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &i = ptr[v]; i < adj[v].size(); ++i) {
            Edge &e = adj[v][i];
            if (level[e.to] != level[v] + 1 || e.cap - e.flow == 0) continue;
            int tr = dfs(e.to, min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            e.flow += tr;
            adj[e.to][e.rev].flow -= tr;
            return tr;
        }
        return 0;
    }

    vector<vector<int>> min_cut() {
        vector<vector<int>> min;
        bool vis[MAXV]{};
        queue<int> q;
        q.push(s); vis[s] = true;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            for (auto it : adj[cur]) {
                if (!vis[it.to] && it.flow < it.cap) {
                    vis[it.to] = true;
                    q.push(it.to);
                }
            }
        }

        for (int i = 0; i < MAXV; ++i) {
            if (!vis[i]) continue;
            for (auto it : adj[i]) {
                if (it.cap > 0 && !vis[it.to]) {
                    min.push_back({i, it.to, it.cap});
                }
            }
        }

        return min;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            fill(ptr, ptr + MAXV, 0);
            while (int pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Debug function to print the graph
    void printGraph(int n) {
        cout << "Graph (Node -> [To, Capacity, Flow]):\n";
        for (int i = 0; i < n; ++i) {
            if (adj[i].empty()) continue; // Skip nodes with no edges
            cout << "Node " << i << ": ";
            for (const auto &e : adj[i]) {
                if(e.cap>0)
                cout << "[" << e.to << ", " << e.cap << ", " << e.flow << "] ";
            }
            cout << "\n";
        }
        cout << "Source: " << s << ", Sink: " << t << "\n";
    }
};

void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    Dinic st;
    st.init(n+m,n+m+1);
    for(int i = 0 ; i < k ; i++){
        int x,y; cin>>x>>y; x--,y--;
        st.addEdge(x,y+n,1);
    }
    for(int i = 0 ; i < n ; i++) st.addEdge(n+m,i,1);
    for(int i  =0 ;i  < m ; i++) st.addEdge(i+n,n+m+1,1);
    cout<<st.maxFlow()<<ln;

    for(int i = 0 ; i < n ; i++){
        for(auto it : st.adj[i]){
            if(it.cap > 0 && it.flow == it.cap){
                cout<<i+1<<" "<<it.to-n+1<<ln;
            }
        }
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