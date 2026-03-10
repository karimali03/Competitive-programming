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

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    void add(int idx, ll val){ // idx is 1..n
        while(idx <= n){
            bit[idx] = (bit[idx] + val);
            idx += idx & -idx;
        }
    }
    ll sumPrefix(int idx){ // sum 1..idx
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1));
    }
};

struct AhoCorasick {
    static const int ALPHABET_SIZE = 26; // 128 (unsgined char)
    static const int BASE = 'a';
    struct Node {
        int next[ALPHABET_SIZE]; // Array of child indices
        int fail;                // Failure link
        int exit_link;
        vector<int>ids;
        int cnt;
        Node() {
            fill(begin(next), end(next), 0);
            cnt = fail = exit_link = 0;
        }
    };

    vector<Node> trie;
    vector<int> bfs_order;
    Fenwick cnt;
    AhoCorasick() {
        // trie.reserve(500005); // Max nodes based on constraints
        trie.emplace_back();
    }

    // Insert a pattern into the trie
    void insert(const string& s,int id) {
        int u = 0;
        for (char c : s) {
            int char_idx = c - BASE;
            if (trie[u].next[char_idx] == 0) {
                trie[u].next[char_idx] = trie.size();
                trie.emplace_back(); // Allocate new node
            }
            u = trie[u].next[char_idx];
        }
        trie[u].cnt++;
    }

    // Build failure links and DFA transitions via BFS
    void build() {
        queue<int> q;

        // Level 1 nodes fail to root (0)
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (trie[0].next[i]) {
                trie[trie[0].next[i]].fail = 0;
                q.push(trie[0].next[i]);
            }
        }

        while (!q.empty()) {
            int u = q.front();  q.pop();
            bfs_order.push_back(u);
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int v = trie[u].next[i];
                if (v) {
                    // Fail link of child is the transition of parent's fail link
                    trie[v].fail = trie[trie[u].fail].next[i];  
                    // Set Dictionary Link
                    if (!trie[trie[v].fail].ids.empty()) {
                        trie[v].exit_link = trie[v].fail;
                    } else {
                        trie[v].exit_link = trie[trie[v].fail].exit_link;
                    } 
                    q.push(v);
                } else {
                    // DFA Optimization: Wire missing edges to the fail state's edges
                    trie[u].next[i] = trie[trie[u].fail].next[i];
                }
            }
        }
    }

    vi in,out;
    vii g;
    void build_failTree(){
        int sz = bfs_order.size();
        in = out = vi(sz);
        g = vii(sz);
        f(i,1,sz) g[trie[i].exit_link].push_back(i); 
        int timer = -1;
        function<void(int)> dfs = [&](int x){
            in[x] = ++timer;
            for(auto &it : g[x]) dfs(it);
            out[x] = timer;
        };
        dfs(0);
        cnt = Fenwick(sz+5);
        f(i,1,sz){
            if(trie[i].cnt){
                cnt.add(in[i]+1,trie[i].cnt);
                cnt.add(out[i]+2,-trie[i].cnt);
            }
        }
    }


    int search(const string& text) {
        int u = 0;
        int res = 0;
        for(int i = 0 ; i < (int)text.size() ; i++){
            auto c = text[i];
            u = trie[u].next[c - BASE];
            res += cnt.sumPrefix(in[u]+1);
        }
        return res;
    }

    // Process text in O(|T|)
    void search(string& text,vi &len,vii &ans) {
        int u = 0;
        for(int i = 0 ; i < (int)text.size() ; i++){
            u = trie[u].next[text[i]-BASE];
            int cur = u;
            if(trie[u].ids.empty()) cur = trie[u].exit_link;
            while(cur){
                for(auto id : trie[cur].ids){
                    ans[id].push_back(i - len[id] + 1);
                }
                cur = trie[cur].exit_link;
            }
        }
      
    }
};

void solve(int test_case) {
    int q,n; cin>>q>>n;
    AhoCorasick ac;
    f(i,0,n){
        string s; cin>>s;
        ac.insert(s,i);
    }
    ac.build();
    ac.build_failTree();
    while(q--){
        char ch; cin>>ch;
        if(ch == '?'){
            string s; cin>>s;
            cout<<ac.search(s)<<ln;
        }else if(ch == '+'){
            int x; cin>>x;
            ac.cnt.add()
        }else{

        }
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