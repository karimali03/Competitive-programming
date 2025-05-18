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


struct DSUWithRollback {
    vector<int> parent, size;
    vector<tuple<int,int,int,int>> history;
    int components;

    DSUWithRollback(int n) : parent(n+1), size(n+1, 1), components(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            history.emplace_back(-1, -1, -1, -1);
            return false;
        }
        if (size[u] < size[v]) std::swap(u, v);
        history.emplace_back(u, v, size[u], size[v]);

        parent[v] = u;
        size[u] += size[v];
        components--;
        return true;
    }

    void rollback() {
        if (history.empty()) return;
        auto [u, v, su, sv] = history.back();
        history.pop_back();
        if (u < 0) return;  // no merge occurred
        parent[u] = u;
        parent[v] = v;
        size[u] = su;
        size[v] = sv;
        components++;
    }

    void checkpoint(){
        history.push_back({-2,-2,-2,-2});
    }

    int count() const {
        return components;
    }

    void snapshot() {
        history.clear();
    }
};

void solve(int test_case) {
    int n,m; cin>>n>>m;
    DSUWithRollback st(n);
    while(m--){
        string s; cin>>s;
        if(s == "persist") st.checkpoint();
        else if(s == "union"){
            int x,y; cin>>x>>y;
            st.unite(x,y);
            cout<<st.count()<<ln;
        }
        else{
            while(true){
                auto [a,b,c,d] = st.history.back();
                st.rollback();
                if(a == -2) break;
            }
            cout<<st.count()<<ln;
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