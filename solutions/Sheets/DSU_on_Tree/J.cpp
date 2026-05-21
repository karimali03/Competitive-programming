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
    static const int MAX_BITS = 30;
    struct node {
        int nxt[2];
        bool leaf;
        int cnt;
        node() {
            leaf = false;
            cnt = 0;
            nxt[0] = nxt[1] = -1;
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void clear(){
        child.clear();
        child.push_back(node());
    }

    void insert(int num){
        int cur = 0;
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

    bool search(int num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(child[cur].nxt[bit] == -1) return false;
            cur = child[cur].nxt[bit];
        }
        return true; 
    }

    int find_max_xor(int num){
        int ret = 0;
        int cur = 0;
        for(int sh = MAX_BITS ; sh >= 0 ; sh--){
            if (cur == -1) break; 
            int bit = (num >> sh)&1;
            
            if(child[cur].nxt[1-bit] != -1){
                ret |= (1 << sh);
                cur = child[cur].nxt[1-bit];
            }else{
                cur = child[cur].nxt[bit];
            }
        }
        return ret;
    }

};



const int N = 200005;
int sz[N] , big[N];
vector<int>g[N];
int color[N];
// Global data structure (e.g., frequency array, max variables)
Trie st;
// answer
vector<pair<int,int>> qu[N];
int ans[N];
// preprocess the tree to compute sizes and identify big children 
void pre(int x,int p){
    sz[x] = 1;
    big[x] = -1;
    for(auto &y : g[x]) if(y != p){
        pre(y,x);
        sz[x] += sz[y];
        if( big[x] == -1 || sz[y] > sz[big[x]]) big[x] = y;
    }
}

void upd(int x){
    st.insert(color[x]);
}

// add or remove the contribution of a subtree rooted at 'x' to the global data structure
void add(int x,int p){
    upd(x);
    for(auto &it : g[x]) if(it != p){
        add(it,x);
    }
}

void sack(int x,int p,int keep){
    // add and remove light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) sack(it,x,0);
    // add big child
    if(~big[x]) sack(big[x],x,1);
    // add myself
    upd(x);
    // add light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) add(it,x);
    // answer queries
    for(auto &[a,b] : qu[x]){
        ans[b] = st.find_max_xor(color[a]);
    }
    // remove if required
    if(!keep){
        st.clear();
    } 
}


void solve(int test_case) {
    int n; cin>>n;
    f(i,0,n) cin>>color[i];
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int q; cin>>q;
    f(i,0,q){
        int x,y; cin>>x>>y; x--,y--;
        qu[y].push_back({x,i});
    }
    pre(0,-1);
    sack(0,-1,1);
    f(i,0,q) cout<<ans[i]<<ln;
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