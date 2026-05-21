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


struct ParallelDSU {
    int n, max_log;
    vector<vector<int>> parent;
 
    ParallelDSU(int n) : n(n) {
        max_log = 0;
        while ((1 << (max_log + 1)) <= n) max_log++;
        max_log++; 
 
        parent.assign(max_log, vector<int>(n));
        for (int k = 0; k < max_log; k++) {
            iota(parent[k].begin(), parent[k].end(), 0);
        }
    }
 
    int get(int k, int i) {
        if (parent[k][i] == i)  return i;
        return parent[k][i] = get(k, parent[k][i]);
    }
 
    // Standard union, but ONLY for layer k. No recursion here.
    void unite(int k, int u, int v) {
        int root_u = get(k, u);
        int root_v = get(k, v);
        if (root_u != root_v) {
            parent[k][root_u] = root_v; 
        }
    }
 
    // Step 1: Add all range constraints
    void unite_range(int u, int v, int len) {
        int k = log2(len);
        unite(k, u, v);
        unite(k, u + len - (1 << k), v + len - (1 << k));
    }
 
    // Step 2: Propagate all constraints down to layer 0
    void push_down() {
        for (int k = max_log - 1; k > 0; k--) {
            for (int i = 0; i < n; i++) {
                // Find the leader of the range starting at i with length 2^k
                int root = get(k, i);
                
                // If i is not its own leader, it means [i, i+2^k) was merged with [root, root+2^k)
                if (root != i) {
                    // Propagate to the two halves in layer k-1
                    int half_len = (1 << (k - 1));
                    unite(k - 1, i, root);
                    unite(k - 1, i + half_len, root + half_len);
                }
            }
        }
    }
 
    // After push_down(), layer 0 contains the final connectivity
    bool connected(int u, int v) {
        return get(0, u) == get(0, v);
    }
};

void solve(int test_case) {
    int n,m; cin>>n>>m;
    ParallelDSU st(n);
    f(i,0,m){
        int a,b,c,d; cin>>a>>b>>c>>d;
        st.unite_range(a-1,c-1,d-c+1);
    }
    st.push_down();
    set<int>s;
    f(i,0,n) s.insert(st.get(0,i));
    cout<<s.size()<<ln;
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