#include <bits/stdc++.h>
using namespace std;
#define ll long long

#define vi vector<ll>
#define vii vector<vi>

const int N = 2e5+10;

ll summ = 0;
vii adj[N];
ll A[N]{}, C[N]{};
ll sol[N]{};

ll dfs(ll u, ll p, ll v) {
    A[u] = v;
    C[u] = 1;
    for (auto &Y : adj[u]) {
        ll neg = Y[0];
        ll a = Y[1];
        ll b = Y[2];
        if (neg == p) continue;
        C[u] += dfs(neg, u, v+a);
    }
    return C[u];
}

void dfs2(ll u, ll p, ll v, ll cnt) {
    v -= C[u]*A[u];
    sol[u] = v;
    // cout << u << ' ' << v << "|\n";
    cnt += C[u];
    for (auto &Y : adj[u]) {
        ll neg = Y[0];
        ll a = Y[1];
        ll b = Y[2];
        if (neg == p) continue;
        
        ll nc = cnt - C[neg];
        ll nv = v + A[u]*C[neg];
        nv += b * nc;
        dfs2(neg, u, nv, nc);
    }
}

void solve(){
    ll n;
    cin >> n;
    for (int i = 0; i < n-1; i++)
    {
        ll u, v, a, b; cin >> u >> v >> a >> b;
        adj[u].push_back({v, a, b});
        adj[v].push_back({u, b, a});
    }
    
    dfs(1, 0, 0);
    dfs2(1, 0, 0, 0);
    for (int i = 0; i <= n; i++)
    {
        summ += A[i];
        // cout << i << ' ' << A[i] << "$\n";
    }

    // cout << summ << "||\n";
    for (int i = 1; i <= n; i++)
    {
        cout << summ + sol[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
