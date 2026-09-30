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
        child.reserve(3100005);
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
    void rm(int num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0; shift--){
            int bit = (num>>shift)&1;
            cur = child[cur].nxt[bit];
            child[cur].cnt--;
        }
    }
    // count (x ^ .. ) < y
    int calc(int x,int y){
        int cur = 0;
        int res = 0;
        for(int i = MAX_BITS ; i >= 0 && cur != -1; i--){
            int bx = (x >> i)&1;
            int by = (y >> i)&1;
            int n0 = child[cur].nxt[0];
            int n1 = child[cur].nxt[1];
            if(bx && by){
                if(n1 != -1) res += child[n1].cnt;
                cur = n0;
            }else if(bx && !by){
                cur = n1;
            }else if(!bx && by){
                if(n0 != -1) res += child[n0].cnt;
                cur = n1;
            }else{
                cur = n0;
            }
        }
        return res;
    }

  

};


void solve(int test_case) {
    int q; cin>>q;
    Trie st;
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int x; cin>>x; 
            st.insert(x);
        }else if(op == 2){
            int x; cin>>x;
            st.rm(x);
        }else{
            int a,b; cin>>a>>b;
            cout<<st.calc(a,b)<<ln;
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