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


const int N = 200005;
vector<int> adj[N];
int tin[N], low[N], timer;
int comp[N], comp_cnt;
stack<int> st;
bool on_stack[N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        tin[i] = low[i] = -1;
        comp[i] = -1;
        on_stack[i] = false;
    }
    while (!st.empty()) st.pop();
    timer = comp_cnt = 0;
}

void dfs(int v) {
    tin[v] = low[v] = timer++;
    st.push(v);
    on_stack[v] = true;

    for (int u : adj[v]) {
        if (tin[u] == -1) {
            dfs(u);
            low[v] = min(low[v], low[u]);
        } else if (on_stack[u]) {
            low[v] = min(low[v], tin[u]);
        }
    }

    if (low[v] == tin[v]) {
        while (true) {
            int u = st.top(); st.pop();
            comp[u] = comp_cnt;
            on_stack[u] = false;
            if (u == v) break;
        }
        comp_cnt++;
    }
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
    }
    f(i,0,n) if(tin[i] == -1) dfs(i);
    cout<<comp_cnt<<ln;
    for(int i  =0;i < n ; i++) cout<<comp_cnt-comp[i]<<" ";
    cout<<ln;
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