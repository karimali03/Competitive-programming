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
        int cnt;
        node() {
            cnt = 0;
            nxt[0] = nxt[1] = -1;
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    bool exist(int cur,int bit){
        return (child[cur].nxt[bit] != -1) && (child[child[cur].nxt[bit]].cnt);
    }
    void insert(int num,int MX){
        int cur = 0;
        for(int shift = MX ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(!exist(cur,bit)){
                child[cur].nxt[bit] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[bit];
            child[cur].cnt++;
        }
    }
       
    int calc(int num,int MX){
        int ret = 0;
        int cur = 0;
        for(int sh = MX ; sh >= 0 && cur != -1; sh--){
            int bit = (num >> sh)&1;
            if(exist(cur,bit)){
                cur = child[cur].nxt[bit];
            }else{
                ret |= (1 << sh);
                cur = child[cur].nxt[1-bit];
            }
        }
        return ret;
    }
    
    


};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    ll res = 0;
    function<void(int,vi&)> dc = [&](int bit,vi &nums){
        if(bit == -1 || nums.empty()) return;
        vi L,R;
        for(auto &it: nums){
            if((it>>bit)&1) R.push_back(it);
            else L.push_back(it);
        }
        dc(bit-1,L); dc(bit-1,R);
        Trie st;
        if(L.empty() || R.empty()) return;
        if(L.size() > R.size()) swap(L,R);
        for(auto &it : L) st.insert(it,bit);
        int mn = INT32_MAX;
        for(auto &it : R) mn = min(mn , st.calc(it,bit));
        res += mn;
    };
    dc(29,v);
    cout<<res<<ln;
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