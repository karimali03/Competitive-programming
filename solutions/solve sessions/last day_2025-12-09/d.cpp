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



/*
 Index-to-Block:
   - block_id = idx / block_size
 Block-to-Index:
   - block_start = block_id * block_size
   - block_end = min(n - 1, (block_id + 1) * block_size - 1)
*/
struct SQRT{
    static const int B = 300;
    vi val;
    vector<pair<int,int>> blocks;

    int n,nb;
    // [l , r)
    pair<int,int> blk_rng(int blk){ 
        return { blk * B , min(n , (blk+1) * B  ) };
    }  

    SQRT(vi &v){
        val = v;
        n = v.size();
        nb = ((n-1)/B)+1;
        blocks = vector<pair<int,int>>(nb,pair<int,int>(-1,-1));
        for(int i = 0;i < n ; i++){
            auto cur = make_pair(v[i],i);
            blocks[i/B] = max(blocks[i/B],cur);
        }
    }

    void update(int x,int y){
        auto rng = blk_rng(x/B);
        val[x] = y;
        for(int i = rng.first ; i  < rng.second ; i++){
            auto cur = make_pair(val[i],i);
            blocks[i/B] = max(blocks[i/B],cur);
        }
    }

    pair<int,int> query(int l,int r){
        int x = l / B , y = r / B;
        pair<int,int> ret = make_pair(-1,-1);
        if(x == y){
            for(int  i = l ; i <= r ; i++){
                auto cur = make_pair(val[i],i);
                ret = max(ret , cur);
            }
            return ret;
        }

        for(int i = l ; i < (x+1) * B ; i++){
            auto cur = make_pair(val[i],i);
            ret = max(ret , cur);
        }
        for(int i = x+1 ; i < y ; i++){
            ret = max(ret , blocks[i]);
        }
        for(int i = y*B ; i <= r ; i++){
            auto cur = make_pair(val[i],i);
            ret = max(ret , cur);
        }
        return ret;
    }
};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    SQRT st(v);
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        auto ret = st.query(l,r);
        cout<<ret.first<<" "<<ret.second+1<<ln;
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