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




const ll INF = (ll)4e18;

struct Floyd {
    int n;

    vector<vector<ll>> dist;
    vector<vector<int>> nxt;

    Floyd(int n) : n(n) {
        dist.assign(n, vector<ll>(n, INF));
        nxt.assign(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
            nxt[i][i] = i;
        }
    }

    // Directed edge u -> v
    void add_directed(int u, int v, ll w) {
        // Important when multiple edges exist
        if (w < dist[u][v]) {
            dist[u][v] = w;
            nxt[u][v] = v;
        }
    }

    // Undirected edge u <-> v
    void add_undirected(int u, int v, ll w) {
        add_directed(u, v, w);
        add_directed(v, u, w);
    }

    // O(n^3)
    void run(int k) {
      //  for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {

                if (dist[i][k] == INF)
                    continue;

                for (int j = 0; j < n; j++) {

                    if (dist[k][j] == INF)
                        continue;

                    ll nd = dist[i][k] + dist[k][j];

                    if (nd < dist[i][j]) {
                        dist[i][j] = nd;
                        // first node after i
                        // on the path i -> ... -> k -> ... -> j
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
     //   }
    }
};

void solve(int test_case) {
    int n; cin>>n;
    Floyd fn(n);
    f(i,0,n) f(j,0,n){
        int x; cin>>x;
        fn.add_directed(i,j,x);
    }
    vi op(n); cin>>op; 
    vi res(n);
    vi active(n);
    for(int i = n-1;i >= 0 ; i--){
        int k = op[i]-1;
        fn.run(k); active[k] = 1;
        int sum = 0;
        for(int x = 0; x < n ; x++){
            if(!active[x]) continue;
            for(int y= 0 ; y < n ; y++){
                if(!active[y]) continue;
                sum += fn.dist[x][y]; 
            }
        }
        res[i] = sum;
    }
   
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}