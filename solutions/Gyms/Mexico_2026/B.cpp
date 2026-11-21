#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pl pair<ll, ll>
#define vp vector<pl>

#define vi vector<ll>
#define vii vector<vi>

const int N = 775;

ll M[N][N]{};
ll D[N][N]{};
const ll INF = 1e16;

void solve(){
    ll n;

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> M[i][j];
        }
    }

    ll m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        ll x1, x2, y1, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    
        D[x1][y1] += k;
        D[x2+1][y2+1] += k;
        D[x2+1][y1] -= k;
        D[x1][y2+1] -= k;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            D[i][j] += D[i-1][j] + D[i][j-1] - D[i-1][j-1];
            if (M[i][j] == -1 || i==j) continue;
            M[i][j] += D[i][j];
        }
    }

    vii dp(n+1, vi(n+1, -1));
    
    for (int src = 1; src <= n; src++)
    {
        vi &dis = dp[src];
        dis[src] = 0;
        priority_queue<pl, vp, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (dis[u] != d) continue;
            // cout << src << ' ' << dis[u] << '\n';
            for (int j = 1; j <= n; j++)
            {
                if (M[u][j] == -1 || u == j) continue;
                ll w = M[u][j] + d;
                if (dis[j] > w || dis[j] == -1) {
                    dis[j] = w;
                    pq.push({w, j});
                }
            }
        }
    }
    

    ll q;cin >> q;
    while (q--)
    {
        ll u, v;
        cin >> u >> v;
        cout << dp[u][v] << '\n';
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
