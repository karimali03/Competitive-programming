#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
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
        fill(level, level + MAXV, -1);
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
vii res;
vi row;
bool vis[MAXV][MAXV]{};
void dfs(int x,Dinic &dic ,int n){
    if(x == n-1) { 
        res.push_back(row);
        return;
    }
    for(auto it : dic.adj[x]){
        if(vis[x][it.to]) continue;
        if( it.flow ==1 && it.cap>0){
            row.push_back(it.to);
            vis[x][it.to] = true;
            dfs(it.to,dic,n);
            row.pop_back();
            return;
        }
    }
}
void solve(int test_case){
    int n,m; cin>>n>>m;
    Dinic dic;
    dic.init(0,n-1);
    for(int i =  0 ; i < m ; i++){
        int a,b; cin>>a>>b; a--,b--;
        dic.addEdge(a,b,1);
    }   
    dic.maxFlow();
  //  dic.printGraph(n);
    row.push_back(0);
    for(auto it :  dic.adj[0]){
        if(it.flow == 1 && it.cap>0){
            row.push_back(it.to);
            dfs(it.to,dic,n);
            row.pop_back();
        }
    }
    cout<<res.size()<<"\n";
    for(auto it : res){
        cout<<it.size()<<"\n";
        for(auto x : it) cout<<x+1<<" ";
        cout<<ln;
    }
}