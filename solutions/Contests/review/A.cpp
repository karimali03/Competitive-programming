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


struct MCMF {
    struct Edge {
        int to, rev;
        ll cap, cost, org;
    };

    int n;
    bool has_neg = false;
    vector<vector<Edge>> g;

    MCMF(int n) : n(n), g(n) {}

    // returns edge index inside g[u]
    int add_edge(int u, int v, ll cap, ll cost) {
        int id = g[u].size();

        g[u].push_back({v, (int)g[v].size(), cap, cost, cap});
        g[v].push_back({u, id, 0, -cost, 0});

        if (cost < 0) has_neg = true;

        return id;
    }

    ll edge_flow(int u, int id) {
        return g[u][id].org - g[u][id].cap;
    }

    pair<ll,ll> min_cost_flow(int s, int t, ll need = 4e18) {
        const ll INF = 4e18;

        vector<ll> pot(n), dist(n);
        vector<int> pv(n), pe(n);

        // Initial potentials if original negative edges exist
        if (has_neg) {
            fill(pot.begin(), pot.end(), INF);
            pot[s] = 0;

            for (int it = 0; it < n - 1; it++) {
                bool changed = false;

                for (int u = 0; u < n; u++) {
                    if (pot[u] == INF) continue;

                    for (auto &e : g[u]) {
                        if (e.cap && pot[e.to] > pot[u] + e.cost) {
                            pot[e.to] = pot[u] + e.cost;
                            changed = true;
                        }
                    }
                }

                if (!changed) break;
            }

            for (auto &x : pot)
                if (x == INF) x = 0;
        }

        ll flow = 0, cost = 0;

        while (flow < need) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;

            priority_queue<
                pair<ll,int>,
                vector<pair<ll,int>>,
                greater<pair<ll,int>>
            > pq;

            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[u]) continue;

                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto &e = g[u][i];

                    if (!e.cap) continue;

                    ll nd = d + e.cost + pot[u] - pot[e.to];

                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dist[t] == INF) break;

            for (int v = 0; v < n; v++)
                if (dist[v] < INF)
                    pot[v] += dist[v];

            ll f = need - flow;

            for (int v = t; v != s; v = pv[v])
                f = min(f, g[pv[v]][pe[v]].cap);

            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];

                cost += f * e.cost;

                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }

            flow += f;
        }

        return {flow, cost};
    }
};

void solve(int test_case) {
    int n,m; cin>>n>>m;
    MCMF st(n+m+2);
    int S = n+m , T = S+1;
    for(int i = 0;i < n ; i++) st.add_edge(S,i,1,0);
    for(int i = 0;i < m ; i++) st.add_edge(i+n,T,1,0);
    int sum = 0;
    for(int i = 0;i < n ; i++){
        int k; cin>>k;
        sum += k;
        for(int j = 0;j < k; j++){
            int a; cin>>a; a--;
            st.add_edge(i,a+n,1,j+1);
        }
    }
    auto res = st.min_cost_flow(S,T,min(n,m));
    cout<<res.first<<" "<< sum - res.second<<ln;
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