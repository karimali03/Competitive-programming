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




struct Trie {
    static const int MAX_BITS = 29;

    struct node {
        int nxt[2];
        int cnt;

        node() {
            cnt = 0;
            nxt[0] = nxt[1] = -1;
        }
    };

    vector<node> child;

    Trie(int n) {
        reserve(1 + n * (MAX_BITS + 1));
        child.push_back(node());
    }

    // Optional speed optimization when the number of insertions is known.
    // Maximum nodes are roughly 1 + inserts * (MAX_BITS + 1).
    void reserve(int nodes) {
        child.reserve(nodes);
    }

    void clear() {
        child.clear();
        child.push_back(node());
    }

    int size() const {
        return child[0].cnt;
    }

    bool empty() const {
        return child[0].cnt == 0;
    }

    // True iff this edge contains at least one currently active number.
    // Important after rm(), because nodes are not physically deleted.
    bool has(int cur, int bit) const {
        int to = child[cur].nxt[bit];
        return to != -1 && child[to].cnt > 0;
    }

    void insert(int num){
        int cur = 0;
        child[cur].cnt++;

        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(child[cur].nxt[bit] == -1){
                child[cur].nxt[bit] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[bit];
            child[cur].cnt++;
        }
    }

    // Maximum VALUE of (num ^ x), over active stored x.
    // On an empty trie the result is 0 (same behavior as the original template).
    int find_max_xor(int num) const {
        int ret = 0;
        int cur = 0;

        for(int sh = MAX_BITS ; sh >= 0 ; sh--){
            if (cur == -1) break;
            int bit = (num >> sh)&1;

            if(has(cur, 1-bit)){
                ret |= (1LL << sh);
                cur = child[cur].nxt[1-bit];
            }else if(has(cur, bit)){
                cur = child[cur].nxt[bit];
            }else{
                break;
            }
        }
        return ret;
    }
};


void solve(int test_case){
    int n; cin>>n;
    vector<vector<pair<int,int>>>g(n);
    for(int i=1;i<n;i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        g[x].push_back({y,z});
        g[y].push_back({x,z});
    }
    Trie st(n);
    vi v(n);
    function<void(int,int,int)> dfs = [&](int x,int p,int val){
        st.insert(val);
        v[x] = val;
        for(auto &[it,w] : g[x]) if(it != p){
            dfs(it,x,val ^ w);
        }
    };
    dfs(0,-1,0);
    for(int i = 0;i < n ; i++){
        cout<<st.find_max_xor(v[i])<<ln;
    }
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