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

int di[]{1,-1,0,0};
int dj[]{0,0,1,-1};

vii adj;
vi cnt;
vec<pair<int,int>> cor;
set<pair<int,int>> points;

void clc(int node, int par) {
    if (points.count(cor[node])) points.erase(cor[node]);
    cor[node] = {INT64_MAX,INT64_MAX};
    for (auto it : adj[node]) {
        if (it == par) continue;
        clc(it, node);
    }
}

bool dfs(int u, int par, int x, int y, int dirFromPar) {
    if (points.count({x, y})) return false;
    points.insert({x, y});
    cor[u] = {x, y};

    vector<int> children;
    for (auto v : adj[u]) {
        if (v != par) children.push_back(v);
    }


    vi all_dirs = {0, 1, 2, 3};
    if (dirFromPar != -1) all_dirs.erase(find(all_dirs.begin(), all_dirs.end(), dirFromPar));
    sort(all_dirs.begin(), all_dirs.end());

    do {
        bool valid = true;
        for (int i = 0; i < (int)children.size(); i++) {
            int pi = all_dirs[i] ^ 1;
            int nx = x + di[all_dirs[i]]*100;
            int ny = y + dj[all_dirs[i]]*100;
            if (!dfs(children[i], u, nx, ny, pi)) {
                valid = false;
                break;
            }
        }
        if (valid) return true;
        for (int i = 0; i < (int)children.size(); i++) clc(children[i], u);

    } while (next_permutation(all_dirs.begin(), all_dirs.end()));

 

    points.erase({x, y});
    cor[u] = {INT64_MAX,INT64_MAX};
    return false;
}

void solve(int test_case) {
    int n; cin >> n;
    adj = vii(n);
    cnt = vi(n, 0);
    cor = vec<pair<int,int>>(n);
    f(i,0,n) cor[i] = {1e18,1e18};

    int st = 0;
    f(i, 0, n - 1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cnt[u]++; cnt[v]++;
    }

    if (*max_element(all(cnt)) > 4) {
        cout << "NO\n";
        return;
    }


    if (dfs(0, -1, 0, 0, -1)) {
            cout << "YES\n";
            for (auto [x, y] : cor) {
                cout << x << " " << y << ln;
            }
            return;
    }
    

    cout << "NO\n";
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