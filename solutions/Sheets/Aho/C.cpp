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
        vector<int>ids;
        vector<int>idx;
        Node() {
            fill(begin(next), end(next), 0);
            fail = exit_link = 0;
        }
    };

    vector<Node> trie;
    vector<int> bfs_order;
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
        trie[u].ids.push_back(id);
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


    void search(const string& text) {
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
    string s; cin>>s;
    int k; cin>>k;
    vi len(k);
    vi x(k);
    AhoCorasick ac;
    f(i,0,k){
        cin>>x[i];
        string a; cin>>a;
        len[i] = a.size();
        ac.insert(a,i);
    }
    vii ans(k);
    ac.build();
    ac.search(s,len,ans);
    vi res(k,1e9);
    for(int i = 0; i < k ; i++){
        int sz = ans[i].size();
    
        for(int j=0; j + x[i] <= sz ; j++){
            int l = ans[i][j] - len[i] + 1;
            int r = ans[i][j+x[i]-1];
            res[i] = min(res[i] , r-l+1);
        }
        if(res[i] == 1e9) NA;
        else cout<<res[i]<<ln;
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