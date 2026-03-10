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

struct AhoCorasick {
    static const int ALPHABET_SIZE = 26; // 128 (unsgined char)
    static const int BASE = 'a';
    struct Node {
        int next[ALPHABET_SIZE]; // Array of child indices
        int fail;                // Failure link
        int exit_link;
        int cnt;
        vector<int>ids;
        Node() {
            fill(begin(next), end(next), 0);
            cnt = fail = exit_link = 0;
        }
    };

    vector<Node> trie;
    vector<int> bfs_order;
    AhoCorasick() {
        // trie.reserve(500005); // Max nodes based on constraints
        trie.emplace_back();
    }

    // Insert a pattern into the trie
    void insert(string& s,int id) {
        int u = 0;
        for (char c : s) {
            int char_idx = c - BASE;
            if (trie[u].next[char_idx] == 0) {
                trie[u].next[char_idx] = trie.size();
                trie.emplace_back(); 
            }
            u = trie[u].next[char_idx];
        }
        trie[u].ids.push_back(id);
        trie[u].cnt++;
    }

    // Build failure links and DFA transitions via BFS
    void build() {
        queue<int> q;
        bfs_order = {0};
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
            for (int i = 0; i < ALPHABET_SIZE; i++){
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
                    trie[v].cnt += trie[trie[v].exit_link].cnt;
                    q.push(v);
                } else {
                    // DFA Optimization: Wire missing edges to the fail state's edges
                    trie[u].next[i] = trie[trie[u].fail].next[i];
                }
            }
        }
    }

    // get the count of patterns in the text
    void search(string& text) {
        int u = 0;
        for(int i = 0 ; i < (int)text.size() ; i++){
            auto c = text[i];
            u = trie[u].next[c - BASE];
            // calc val for trie[u]
        }
        int sz = bfs_order.size();
        for(int i = sz-1 ; i >= 0 ; i--){
            auto it = bfs_order[i];
            // propagate val to trie[it].fail
        }
    }

    // get the starting indices of all patterns in the text
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

    vi in,out;
    vii g;
    // Build a tree of fail links for subtree queries
    // use Fenwick Tree or Segment Tree to quickly query how many patterns are active in the subtree of a node.
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
    }

};


int dp[1005][21][2][2][2];
const int MOD = 1000003;
void solve(int test_case) {
   int l,r; cin>>l>>r;
   int n; cin>>n;
   AhoCorasick ac;
   for(int i = 0;i < n ; i++){
        string s; cin>>s;
        ac.insert(s,i);
   }
   ac.build();
   memset(dp,-1,sizeof(dp));
   vi digit(10,26);
   digit[0] = 'o'-'a';
   digit[1] = 'i'-'a';
   digit[3] = 'e'-'a';
   digit[5] = 's'-'a';
   digit[7] = 't'-'a';
   function<int(int,int,int,int,int)> rec = [&](int i,int len,int x,int y,int z) -> int{
        if(len == r) return x && y && z && (!ac.trie[i].cnt);
        int &ret = dp[i][len][x][y][z];
        if(~ret) return ret;
        if(ac.trie[i].cnt) return ret = 0;
        ret = 0;
        if(len >= l && x && y && z) ret = 1;
        for(int ch = 0;ch < 26 ; ch++){
            (ret += rec(ac.trie[i].next[ch],len+1,1,y,z))%=MOD;
            (ret += rec(ac.trie[i].next[ch],len+1,x,1,z))%=MOD;
        }
        for(int ch = 0;ch < 10 ; ch++){
            (ret += rec(ac.trie[i].next[digit[ch]],len+1,x,y,1))%=MOD;
        }
        return ret;
   };
   cout<<rec(0,0,0,0,0)<<ln;
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