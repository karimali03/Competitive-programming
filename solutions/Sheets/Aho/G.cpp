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
    static const int ALPHABET_SIZE = 10; // 128 (unsgined char)
    static const int BASE = '0';
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
    void insert(string& s) {
        int u = 0;
        for (char c : s) {
            int char_idx = c - BASE;
            if (trie[u].next[char_idx] == 0) {
                trie[u].next[char_idx] = trie.size();
                trie.emplace_back(); 
            }
            u = trie[u].next[char_idx];
        }
        trie[u].ids.push_back(0);
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

    // int search(const string& text) {
    //     int u = 0;
    //     int res = 0;
    //     for(int i = 0 ; i < (int)text.size() ; i++){
    //         auto c = text[i];
    //         u = trie[u].next[c - BASE];
    //         res += cnt.sumPrefix(in[u]+1);
    //     }
    //     return res;
    // }

};

string cur;
int sum;
int x;
bool chk(){
    int sz = cur.size();
    for(int i = 0; i < sz ; i++){
        int s = 0;
        for(int j = i ; j < sz ; j++){
            s += cur[j]-'0';
            if(i == 0 && j == sz-1) continue;
            if(x%s == 0) return false;
        }
    }
    return true;
}

vector<string> res;
AhoCorasick ac;
void bt(){
    if(sum == x){
        if(chk()) ac.insert(cur);
        return;
    }
    for(int i = 1 ; i < 10 ; i++){
        if(i+sum > x) break;
        sum += i;
        cur.push_back(i+'0');
        bt();
        cur.pop_back();
        sum -= i;
    }
}

int dp[1005][100];
string s; 

int rec(int i,int u){
    if(i == (int)s.size()) return 0;
    int &ret = dp[i][u];
    if(~ret) return ret;
    ret = 1 + rec(i+1,u);
    int nxt = ac.trie[u].next[s[i]-'0'];
    if(ac.trie[nxt].cnt == 0) ret = min(ret , rec(i+1,nxt));
    return ret;
}
void solve(int test_case) {
    cin>>s>>x;
    bt();
    cout<<ac.trie.size()<<ln;
    ac.build();
    memset(dp,-1,sizeof(dp));
    cout<<rec(0,0)<<ln;
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