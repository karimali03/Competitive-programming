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


const int MAXV = 251005;
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
        memset(level, -1, sizeof(level));
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
            if (level[e.to] != level[v] + 1 || e.flow == e.cap) continue;
            int tr = dfs(e.to, min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            e.flow += tr;
            adj[e.to][e.rev].flow -= tr;
            return tr;
        }
        return 0;
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

    vector<vector<int>> paths;

    bool dfs_path(int u, vector<int> &path) {
        if (u == t) {
            paths.push_back(path);
            return true;
        }
        for (auto &e : adj[u]) {
            if (e.cap > 0 && e.flow == e.cap) {
                path.push_back(e.to);
                e.flow = 0; // mark used
                if (dfs_path(e.to, path)) return true;
                path.pop_back();
                e.flow = e.cap; // backtrack
            }
        }
        return false;
    }

    vector<vector<int>> getAllFlowPaths() {
        paths.clear();
        while (true) {
            vector<int> path = {s};
            if (!dfs_path(s, path)) break;
        }
        return paths;
    }

    void printGraph(int n) {
        cout << "Graph (Node -> [To, Cap, Flow]):\n";
        for (int i = 0; i < n; ++i) {
            if (adj[i].empty()) continue;
            cout << "Node " << i << ": ";
            for (const auto &e : adj[i]) {
                if (e.cap > 0)
                    cout << "[" << e.to << ", " << e.cap << ", " << e.flow << "] ";
            }
            cout << "\n";
        }
    }
};


void solve(int test_case) {
    int n; cin>>n;
    int cnt = 0;
    Dinic st;
    int s = 0 , t = 1;
    int BR = 2 + n*n;
    int BC = BR + n; 
    st.init(s,t);
    for(int i = 0;i < n ; i++){
        for(int j = 0; j < n ; j++){
            int x; cin>>x; 
            if(x > 1){
                st.addEdge(s,i*n+j+2,x-1);
                st.addEdge(i*n+j+2,BR+i,x-1);
                st.addEdge(i*n+j+2,BC+j,x-1);
            }else if(x == 0){
                st.addEdge(i*n+j+2,t,1);
                st.addEdge(BR+i,i*n+j+2,1);
                st.addEdge(BC+j,i*n+j+2,1);
                cnt++;
            }
        }
    }
  
    int res = 2 * cnt - st.maxFlow();
    cout << res<<ln;
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