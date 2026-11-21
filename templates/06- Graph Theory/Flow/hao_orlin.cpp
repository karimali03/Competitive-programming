#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Directed global minimum cut (Hao-Orlin, push-relabel with changing sinks).
// n >= 2; vertices 0..n-1; nonnegative capacities; parallel edges allowed.
// Returns {minimum outgoing cut capacity, vertices on source side}.
// Directed Global Min Cut - Hao Orlin
// Conservative estimate: O(V^2 * E), memory O(V + E)
// Sparse: O(V^3), Dense: O(V^4)
// Optimized Hao-Orlin: O(V * E * log(V^2 / E))
struct HaoOrlin {
    struct Arc { int u, v; ll c; };
    int n;
    vector<Arc> edges;
    HaoOrlin(int n) : n(n) {}
    void addEdge(int u, int v, ll c) { if (u != v) edges.push_back({u, v, c}); }

    pair<ll, vector<int>> rooted(bool rev) const {
        vector<vector<int>> g(n);
        vector<int> to;
        vector<ll> res;
        for (auto [u0, v0, c] : edges) {
            int u = rev ? v0 : u0, v = rev ? u0 : v0;
            int id = (int)to.size();
            g[u].push_back(id); to.push_back(v); res.push_back(c);
            g[v].push_back(id ^ 1); to.push_back(u); res.push_back(0);
        }
        vector<ll> excess(n, 0);
        vector<int> d(n, 0), cnt(2*n+5, 0);
        vector<char> source(n, 0), awake(n, 1);
        vector<vector<int>> dormant;
        source[0] = 1; awake[0] = 0; d[0] = n;
        cnt[0] = n-1;

        auto push = [&](int id, ll amt) {
            res[id] -= amt; res[id^1] += amt;
            excess[to[id^1]] -= amt;
            excess[to[id]] += amt;
        };
        auto sleep = [&](vector<int> group) {
            for (int v : group) { awake[v] = 0; --cnt[d[v]]; }
            dormant.push_back(move(group));
        };
        for (int id : g[0]) if (res[id] > 0) push(id, res[id]);

        ll best = LLONG_MAX;
        vector<int> bestSide;
        int t = 1;
        for (int phase = 0; phase < n-1; ++phase) {
            queue<int> q;
            for (int v = 0; v < n; ++v)
                if (awake[v] && v != t && excess[v] > 0) q.push(v);
            vector<int> it(n, 0);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                while (awake[v] && v != t && excess[v] > 0) {
                    if (it[v] < (int)g[v].size()) {
                        int id = g[v][it[v]], w = to[id];
                        if (res[id] > 0 && awake[w] && d[v] == d[w]+1) {
                            ll amount = min(excess[v], res[id]);
                            bool activate = (w != t && excess[w] == 0);
                            push(id, amount);
                            if (activate) q.push(w);
                        } else ++it[v];
                        continue;
                    }
                    it[v] = 0;
                    if (cnt[d[v]] == 1) {  // Gap: all higher levels become dormant.
                        vector<int> group;
                        for (int w=0; w<n; ++w)
                            if (awake[w] && d[w] >= d[v]) group.push_back(w);
                        sleep(move(group));
                    } else {
                        int md = INT_MAX;
                        for (int id : g[v])
                            if (res[id] > 0 && awake[to[id]]) md = min(md, d[to[id]]);
                        if (md == INT_MAX) sleep({v});
                        else {
                            --cnt[d[v]];
                            d[v] = md+1;
                            ++cnt[d[v]];
                        }
                    }
                }
            }
            ll value = 0;
            for (auto [u, v, c] : edges) {
                if (rev) swap(u, v);
                if (!awake[u] && awake[v]) value += c;
            }
            if (value < best) {
                best = value;
                bestSide.clear();
                for (int v = 0; v < n; ++v) if (!awake[v]) bestSide.push_back(v);
            }
            source[t] = 1; awake[t] = 0; --cnt[d[t]]; d[t] = n;
            for (int id : g[t])
                if (res[id] > 0 && !source[to[id]]) push(id, res[id]);
            bool any = false;
            for (int v=0; v<n; ++v) any |= bool(awake[v]);
            if (!any && !dormant.empty()) {
                auto group = move(dormant.back()); dormant.pop_back();
                for (int v : group) { awake[v] = 1; ++cnt[d[v]]; }
            }
            int nt=-1;
            for (int v=0; v<n; ++v)
                if (awake[v] && (nt == -1 || d[v] < d[nt])) nt=v;
            if (nt == -1) break;
            t = nt;
        }
        return {best, bestSide};
    }

    pair<ll, vector<int>> minCut() const {
        auto a = rooted(false), b = rooted(true);
        if (a.first <= b.first) return a;
        vector<char> in(n, false);
        for (int v : b.second) in[v] = true;
        vector<int> side;
        for (int v=0; v<n; ++v) if (!in[v]) side.push_back(v);
        return {b.first, side};
    }
};

int main(){
  ios::sync_with_stdio(false);cin.tie(nullptr);
  int n,m;cin>>n>>m;
  HaoOrlin hc(n);
  for(int i=0;i<m;i++){int u,v; ll w;cin>>u>>v>>w; hc.addEdge(u,v,w);}
  auto [val, side] = hc.minCut();
  cout << val << '\n';
  cout << side.size(); for(int v:side) cout << ' ' << v; cout << '\n';
}
